/*
*  GeomMesh.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoMesh.h"
#include "GeoElementSide.h"
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
	int64_t nNodes = NumNodes();//N�mero de n�s da malha
	int64_t nElements = NumElements();//N�mero de elementos da malha

	VecInt SideNum(nNodes, -1); //Cria um vetor de lados iniciais ligados aos n�s da malha
	std::vector<GeoElement *> NeighNode(nNodes, 0);//Cria um vetor de elementos iniciais ligados aos n�s da malha

	for (int i = 0; i < nElements; i++)//Cria��o de vizinhan�a para os lados extremos dos elementos
	{
		GeoElement *gel = Elements[i];//Aponta para o elemento "i" da lista de elementos da malha

		if (!gel)//Se existir um elemento continue
		{
			continue;
		}

		int nCorners = gel->NCornerNodes();//N�mero de n�s do elemento "i"

		for (int j = 0; j < nCorners; j++)
		{
			int64_t NodeId = gel->NodeIndex(j);//Aponta para o n� da malha em que extremidade "j" do elemento "i" � ligado
			
			if (SideNum[NodeId]==-1)//Se n�o existir um vizinho inicial no n� "NodeId", inseri-lo
			{
				GeoElementSide NewNeighbour(gel, j);//Cria um "GeoElementSide" do elemento "i" com lado "j"
				gel->SetNeighbour(j, NewNeighbour);//Insere o lado "j" do elemento "i" como vizinho dele mesmo

				NeighNode[NodeId] = gel;//Insere o elemento "i" no vetor de elementos iniciais da malha
				SideNum[NodeId] = j;//Insere o lado "j" do elemento "i" no vetor de lados iniciais da malha
			}

			else//Caso j� exista um vizinho inicial no n� "NodeId" insira o elemento "i" na vizinhan�a
			{
				GeoElementSide NewNeighbour(gel, j);//Cria um "GeoElementSide" do elemento "i" com lado "j"
				GeoElementSide LastNeigh = NeighNode[NodeId]->Neighbour(SideNum[NodeId]);//Copia o �ltimo vizinho inserido no n� "NodeId"
				
				gel->SetNeighbour(j, LastNeigh);//Insere o �ltimo vizinho do "NodeId" como vizinho do lado "j" do elemento "i"
				NeighNode[NodeId]->SetNeighbour(SideNum[NodeId], NewNeighbour);//Insere o lado "j" do elemento "i" na vizinhan�a do n� "NodeId"
			}
		}
	}

	for (int i = 0; i < nElements; i++)//Cria��o de vizinha�a para os n�s internos
	{
		GeoElement *gel = Elements[i];//Aponta para o elemento "i" da lista de elementos da malha

		if (!gel)//Se existir um elemento continue
		{
			continue;
		}

		int nCorners = gel->NCornerNodes();//N�mero de n�s do elemento "i"
		int nSides = gel->NSides();//N�mero de lados do elemento "i"

		for (int j = nCorners; j < nSides; j++)
		{
			GeoElementSide gelside(gel, j);//Cria um "GeoElementSide" do elemento "i" com lado "j"
			std::vector <GeoElementSide> neighbour(1);//Cria vetor de vizinhos do lado "j" do elemento "i"
			neighbour[0] = gelside;//Inicia o vetor de vizinhos com ele mesmo

			gelside.ComputeNeighbours(neighbour);//Computa dos vizinhos do lado "j" do elemento "i"

			gel->SetNeighbour(j, neighbour[0]);//Insere o vizinho do lado "j" do elemento "i"

		}
	}
}

void GeoMesh::Print(std::ostream &out)
{
	out << "\n\t MESH INFORMATIONS:\n\n";
	out << "NUMBER OF NODES = " << NumNodes() << "\n";
	out << "NUMBER OF ELEMENTS = " << NumElements() << "\n";

	out << "\n\n\t NODES INFORMATIONS:\n\n";
	for (int i = 0; i < NumNodes(); i++)
	{
		out << "NODE: " << i << "\t";
		Nodes[i].Print(out);
	}
	out << "\n\n\t ELEMENTS INFORMATIONS:\n\n";
	int64_t nelem = Elements.size();
	for (int i = 0; i<nelem; i++)
	{
		if (Elements[i]) Elements[i]->Print(out);
	}
}