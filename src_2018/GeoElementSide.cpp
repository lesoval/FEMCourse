/*
*  GeomElementSide.cpp
*
*  Created by Leandro Valdez on 4/22/18.
*
*/

#include "GeoElementSide.h"
#include "tpanic.h"

GeoElementSide::GeoElementSide() {}

GeoElementSide::GeoElementSide(const GeoElementSide &copy)
{
	this->operator=(copy);
}

GeoElementSide &GeoElementSide::operator=(const GeoElementSide &copy)
{
	fSide = copy.fSide;
	fElement = copy.fElement;

	return *this;
}

GeoElementSide GeoElementSide::Neighbour() const
{
	return fElement->Neighbour(fSide);
}

void GeoElementSide::SetNeighbour(const GeoElementSide & neighbour)
{
	fElement->SetNeighbour(fSide, neighbour);
}

bool GeoElementSide::IsNeighbour(const GeoElementSide & candidate)//Não utilizado
{
	return false;
}

void GeoElementSide::IsertConnectivity(GeoElementSide & connectivity)//Não utilizado
{
}

void GeoElementSide::AllNeighbours(std::vector<GeoElementSide>& allneigh)
{
	GeoElementSide NodeNeigh = Neighbour();

	if (*this == NodeNeigh)//Caso seja vizinho dele mesmo
	{
		allneigh.push_back(NodeNeigh);//Insere ele mesmo como vizinho
	}

	while (*this != NodeNeigh)//Enquanto o elemento não repete, prossiga
	{
		allneigh.push_back(NodeNeigh);//Insere o vizinho do nó "k" na vizinhança do lado "j"
		NodeNeigh = NodeNeigh.Neighbour();//Copia o próximo vizinho do nó "k"
	}
}

void GeoElementSide::ComputeNeighbours(std::vector<GeoElementSide>& neighbour)
{
	GeoElement *gel = this->fElement;
	int side = this->fSide;
	int nSideNodes = gel->NSideNodes(side);//Número de nós ligados ao lado "j"
	int NodeLocId;//Indices dos nós ligados ao lado "j"
	std::vector<GeoElementSide> AllNeigh;//Cria um vetor de todos os vizinhos dos nós ligados ao lado "j"

	for (int i = 0; i < nSideNodes; i++)
	{
		NodeLocId = gel->SideNodeIndex(side, i);//Insere os indices locais dos nós ligados ao lado "j"
		GeoElementSide LocSide(gel, NodeLocId);//Cria um "GeoElementSide" do nó "k" ligado ao lado "j"

		LocSide.AllNeighbours(AllNeigh);
	}

	switch (nSideNodes)
	{
	case 2://Lado com 2 vétices

		for (int i = 0; i < AllNeigh.size() - 1; i++)
		{
			for (int j = i + 1; j < AllNeigh.size(); j++)
			{
				if (AllNeigh[i].Element()->GetIndex() == AllNeigh[j].Element()->GetIndex())
				{
					GeoElement *el = AllNeigh[i].Element();
					VecInt side(nSideNodes);

					side[0] = AllNeigh[i].Side();
					side[1] = AllNeigh[j].Side();

					GeoElementSide neigh(el, el->WhichSide(side));

					neighbour[0] = neigh;
				}
			}
		}

		break;

	case 3://Lado com 3 vértices

		for (int i = 0; i < AllNeigh.size() - 2; i++)
		{
			for (int j = i + 1; j < AllNeigh.size() - 1; j++)
			{
				for (int k = j + 1; k < AllNeigh.size(); k++)
				{
					if (AllNeigh[i].Element()->GetIndex() == AllNeigh[j].Element()->GetIndex()
						&& AllNeigh[j].Element()->GetIndex() == AllNeigh[k].Element()->GetIndex())
					{
						GeoElement *el = AllNeigh[i].Element();
						VecInt side(nSideNodes);

						side[0] = AllNeigh[i].Side();
						side[1] = AllNeigh[j].Side();
						side[2] = AllNeigh[k].Side();

						GeoElementSide neigh(el, el->WhichSide(side));

						neighbour[0] = neigh;
					}
				}
			}
		}

		break;

	case 4://Lado com 4 vértices

		for (int i = 0; i < AllNeigh.size() - 3; i++)
		{
			for (int j = i + 1; j < AllNeigh.size() - 2; j++)
			{
				for (int k = j + 1; k < AllNeigh.size() - 1; k++)
				{
					for (int l = k + 1; l < AllNeigh.size(); l++)
					{
						if (AllNeigh[i].Element()->GetIndex() == AllNeigh[j].Element()->GetIndex()
							&& AllNeigh[j].Element()->GetIndex() == AllNeigh[k].Element()->GetIndex()
							&& AllNeigh[k].Element()->GetIndex() == AllNeigh[l].Element()->GetIndex())
						{
							GeoElement *el = AllNeigh[i].Element();
							VecInt side(nSideNodes);

							side[0] = AllNeigh[i].Side();
							side[1] = AllNeigh[j].Side();
							side[2] = AllNeigh[k].Side();
							side[3] = AllNeigh[l].Side();

							GeoElementSide neigh(el, el->WhichSide(side));

							neighbour[0] = neigh;
						}
					}
				}
			}
		}

		break;

	default:

		std::cout << "GeoElementSide::ComputeNeighbours : Inconsistent geometrie detected" << std::endl;
		DebugStop();

		break;
	}
}
