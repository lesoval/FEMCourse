/*
*  GeomMesh.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoMesh.h"
#include "tpanic.h"

GeoMesh::GeoMesh() {}

GeoMesh::GeoMesh(const GeoMesh &copy)
{
	this->operator=(copy);
}

GeoMesh &GeoMesh::operator=(const GeoMesh &copy)
{
	Nodes = copy.Nodes;
	Elements = copy.Elements;

	return *this;
}

void GeoMesh::SetNumNodes(int nnodes)
{
	Nodes.resize(nnodes);
}

void GeoMesh::SetNumElements(int numelements)
{
	Elements.resize(numelements);
}

int GeoMesh::NumNodes()
{
	return Nodes.size();
}

int GeoMesh::NumElements()
{
	return Elements.size();
}

GeoNode &GeoMesh::Node(int node)
{
	return Nodes[node];
}

void GeoMesh::SetElement(int elindex, GeoElement *gel)
{
	Elements[elindex] = gel;
}

GeoElement *GeoMesh::Element(int elindex)
{
	return Elements[elindex];
}

void GeoMesh::BuildConnectivity()
{
	int64_t nNodes = NumNodes();//Número de nós da malha
	int64_t nElements = NumElements();//Número de elementos da malha

	VecInt SideNum(nNodes, -1); //Cria um vetor de lados iniciais ligados aos nós da malha
	std::vector<GeoElement *> NeighNode(nNodes, 0);//Cria um vetor de elementos iniciais ligados aos nós da malha

	for (int i = 0; i < nElements; i++)//Criação de vizinhança para os lados extremos dos elementos
	{
		GeoElement *gel = Elements[i];//Aponta para o elemento "i" da lista de elementos da malha

		if (!gel)//Se existir um elemento continue
		{
			continue;
		}

		int nCorners = gel->NCornerNodes();//Número de nós do elemento "i"

		for (int j = 0; j < nCorners; j++)
		{
			int64_t NodeId = gel->NodeIndex(j);//Aponta para o nó da malha em que extremidade "j" do elemento "i" é ligado
			
			if (SideNum[NodeId]==-1)//Se não existir um vizinho inicial no nó "NodeId", inseri-lo
			{
				GeoElementSide NewNeighbour(gel, j);//Cria um "GeoElementSide" do elemento "i" com lado "j"
				gel->SetNeighbour(j, NewNeighbour);//Insere o lado "j" do elemento "i" como vizinho dele mesmo

				NeighNode[NodeId] = gel;//Insere o elemento "i" no vetor de elementos iniciais da malha
				SideNum[NodeId] = j;//Insere o lado "j" do elemento "i" no vetor de lados iniciais da malha
			}

			else//Caso já exista um vizinho inicial no nó "NodeId" insira o elemento "i" na vizinhança
			{
				GeoElementSide NewNeighbour(gel, j);//Cria um "GeoElementSide" do elemento "i" com lado "j"
				GeoElementSide LastNeigh = NeighNode[NodeId]->Neighbour(SideNum[NodeId]);//Copia o último vizinho inserido no nó "NodeId"
				
				gel->SetNeighbour(j, LastNeigh);//Insere o último vizinho do "NodeId" como vizinho do lado "j" do elemento "i"
				NeighNode[NodeId]->SetNeighbour(SideNum[NodeId], NewNeighbour);//Insere o lado "j" do elemento "i" na vizinhança do nó "NodeId"
			}
		}
	}

	for (int i = 0; i < nElements; i++)//Criação de vizinhaça para os nós internos
	{
		GeoElement *gel = Elements[i];//Aponta para o elemento "i" da lista de elementos da malha

		if (!gel)//Se existir um elemento continue
		{
			continue;
		}

		int nCorners = gel->NCornerNodes();//Número de nós do elemento "i"
		int nSides = gel->NSides();//Número de lados do elemento "i"

		for (int j = nCorners; j < nSides; j++)
		{
			GeoElementSide gelside(gel, j);//Cria um "GeoElementSide" do elemento "i" com lado "j"
			GeoElementSide neighbour = gelside;//Inicia o vizinho como sendo ele mesmo

			//ComputeNeighbours
			int nSideNodes = gel->NSideNodes(j);//Número de nós ligados ao lado "j"
			int NodeLocId;//Cria vetor de indices dos nós ligados ao lado "j"
			std::vector<GeoElementSide> AllNeigh;//Cria um vetor de todos os vizinhos dos nós ligados ao lado "j"

			for (int k = 0; k < nSideNodes; k++)
			{
				NodeLocId = gel->SideNodeIndex(j, k);//Insere os indices locais dos nós ligados ao lado "j"
				GeoElementSide LocSide(gel, NodeLocId);//Cria um "GeoElementSide" do nó "k" ligado ao lado "j"
				GeoElementSide NodeNeigh = gel->Neighbour(NodeLocId);//Copia o vizinho do nó "k"

				if (LocSide.Element()->GetIndex() == NodeNeigh.Element()->GetIndex())//Caso seja vizinho dele mesmo
				{
					AllNeigh.push_back(NodeNeigh);//Insere ele mesmo como vizinho
				}

				while (LocSide.Element()->GetIndex() != NodeNeigh.Element()->GetIndex())//Enquanto o elemento não repete, prossiga
				{
					AllNeigh.push_back(NodeNeigh);//Insere o vizinho do nó "k" na vizinhança do lado "j"
					NodeNeigh = NodeNeigh.Neighbour();//Copia o próximo vizinho do nó "k"
				}
			}

			switch (nSideNodes)
			{
			case 2://Lado com 2 vétices

				for (int k = 0; k < AllNeigh.size() - 1; k++)
				{
					for (int l = k + 1; l < AllNeigh.size(); l++)
					{
						if (AllNeigh[k].Element()->GetIndex() == AllNeigh[l].Element()->GetIndex())
						{
							GeoElement *el = AllNeigh[k].Element();
							int side;

							int side1 = AllNeigh[k].Side();
							int side2 = AllNeigh[l].Side();

							for (int p = el->NCornerNodes(); p < el->NSides(); p++)
							{
								if ((side1 == el->SideNodeIndex(p, 0) && side2 == el->SideNodeIndex(p, 1)) ||
									(side2 == el->SideNodeIndex(p, 0) && side1 == el->SideNodeIndex(p, 1)))
								{
									side = p;
								}
							}

							GeoElementSide neigh(el, side);

							neighbour = neigh;
						}
					}
				}

				break;

			case 3://Lado com 3 vértices

				for (int k = 0; k < AllNeigh.size() - 2; k++)
				{
					for (int l = k + 1; l < AllNeigh.size() - 1; l++)
					{
						for (int m = l + 1; m < AllNeigh.size(); m++)
						{
							if (AllNeigh[k].Element()->GetIndex() == AllNeigh[l].Element()->GetIndex()
								&& AllNeigh[l].Element()->GetIndex() == AllNeigh[m].Element()->GetIndex())
							{
								GeoElement *el = AllNeigh[k].Element();
								int side;

								int side1 = AllNeigh[k].Side();
								int side2 = AllNeigh[l].Side();
								int side3 = AllNeigh[m].Side();

								for (int p = el->NCornerNodes(); p < el->NSides(); p++)
								{
									if ((side1 == el->SideNodeIndex(p, 0) && side2 == el->SideNodeIndex(p, 1) && side3 == el->SideNodeIndex(p, 2)) ||
										(side2 == el->SideNodeIndex(p, 0) && side3 == el->SideNodeIndex(p, 1) && side1 == el->SideNodeIndex(p, 2)) ||
										(side3 == el->SideNodeIndex(p, 0) && side1 == el->SideNodeIndex(p, 1) && side2 == el->SideNodeIndex(p, 2)))
									{
										side = p;
									}
								}

								GeoElementSide neigh(el, side);

								neighbour = neigh;
							}
						}
					}
				}

				break;

			case 4://Lado com 4 vértices

				for (int k = 0; k < AllNeigh.size() - 3; k++)
				{
					for (int l = k + 1; l < AllNeigh.size() - 2; l++)
					{
						for (int m = l + 1; m < AllNeigh.size() - 1; m++)
						{
							for (int n = m + 1; n < AllNeigh.size(); n++)
							{
								if (AllNeigh[k].Element()->GetIndex() == AllNeigh[l].Element()->GetIndex()
									&& AllNeigh[l].Element()->GetIndex() == AllNeigh[m].Element()->GetIndex()
									&& AllNeigh[m].Element()->GetIndex() == AllNeigh[n].Element()->GetIndex())
								{
									GeoElement *el = AllNeigh[k].Element();
									int side;

									int side1 = AllNeigh[k].Side();
									int side2 = AllNeigh[l].Side();
									int side3 = AllNeigh[m].Side();
									int side4 = AllNeigh[n].Side();

									for (int p = el->NCornerNodes(); p < el->NSides(); p++)
									{
										if ((side1 == el->SideNodeIndex(p, 0) && side2 == el->SideNodeIndex(p, 1) && side3 == el->SideNodeIndex(p, 2) && side4 == el->SideNodeIndex(p, 3)) ||
											(side2 == el->SideNodeIndex(p, 0) && side3 == el->SideNodeIndex(p, 1) && side4 == el->SideNodeIndex(p, 2) && side1 == el->SideNodeIndex(p, 3)) ||
											(side3 == el->SideNodeIndex(p, 0) && side4 == el->SideNodeIndex(p, 1) && side1 == el->SideNodeIndex(p, 2) && side2 == el->SideNodeIndex(p, 3)) ||
											(side4 == el->SideNodeIndex(p, 0) && side1 == el->SideNodeIndex(p, 1) && side2 == el->SideNodeIndex(p, 2) && side3 == el->SideNodeIndex(p, 3)))
										{
											side = p;
										}
									}

									GeoElementSide neigh(el, side);

									neighbour = neigh;
								}
							}
						}
					}
				}

				break;

			default:

				std::cout << "GeoMesh::BuildConnectivity : Inconsistent geometrie detected" << std::endl;
				DebugStop();

				break;
			}

			gel->SetNeighbour(j, neighbour);

		}
	}
}

void GeoMesh::Print(std::ostream &out)
{
	out << "\n\t MESH INFORMATIONS:\n\n";
	out << "NUMBER OF NODES = " << NumNodes() << "\n";
	out << "NUMBER OF ELEMENTS = " << NumElements() << "\n";

	out << "\n\t NODES INFORMATIONS:\n\n";
	for (int i = 0; i < NumNodes(); i++)
	{
		out << "NODE: " << i << "\t";
		Nodes[i].Print(out);
	}
	out << "\n\t ELEMENTS INFORMATIONS:\n\n";
	int64_t nelem = Elements.size();
	for (int i = 0; i<nelem; i++)
	{
		if (Elements[i]) Elements[i]->Print(out);
	}
	out << "\n";
}