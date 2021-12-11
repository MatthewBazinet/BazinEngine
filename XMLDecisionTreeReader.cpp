#include "XMLDecisionTreeReader.h"

DecisionTreeNode XMLDecisionTreeReader::ReadFile(const char* filepath_)
{
	XMLDocument doc;
	doc.LoadFile(filepath_);
	bool status = doc.Error();
	if (status) {
		std::cout << doc.ErrorIDToName(doc.ErrorID()) << std::endl;
	}
	std::vector<XMLElement*> tmp_decisionNode;
	std::vector<std::string> decisionNode;
	XMLDecision decision;
	tmp_decisionNode[0] = doc.FirstChildElement("decisionTree");
	std::vector<XMLElement*> branchT;
	std::vector<XMLElement*> branchF;
	DecisionTreeNode* tmpT;
	DecisionTreeNode* tmpF;
	int counter = 1;
	int i = 0;
	if (tmp_decisionNode[i]->FirstChild() == tmp_decisionNode[i]->FirstChildElement("test")) {
		tmp_decisionNode[i + 1] = tmp_decisionNode[i]->FirstChildElement("test");//first test node
		decisionNode.push_back(tmp_decisionNode[i]->FirstChildElement("test")->GetText());
		//decision[i]->SetTrueNode(tmpT);
		//decision[i]->SetFalseNode(tmpF);
		branchT[i] = tmp_decisionNode[i]->FirstChildElement("true");
		branchF[i] = tmp_decisionNode[i]->FirstChildElement("false");
		tmpT = nullptr;
		tmpF = nullptr;
	}

	while (true) {

		if (tmp_decisionNode[i]->FirstChild() == tmp_decisionNode[i]->FirstChildElement("test")) {
			tmp_decisionNode[i + 1] = tmp_decisionNode[i]->FirstChildElement("test");//first test node
			decisionNode.push_back(tmp_decisionNode[i]->FirstChildElement("test")->GetText());
			//decision[i]->SetTrueNode(tmpT);
			//decision[i]->SetFalseNode(tmpF);
			branchT[i] = tmp_decisionNode[i]->FirstChildElement("true");
			branchF[i] = tmp_decisionNode[i]->FirstChildElement("false");
			tmpT = nullptr;
			tmpF = nullptr;
		}else if (branchT[i]->FirstChild() == branchT[i]->FirstChildElement("test")) {//true branch
			tmp_decisionNode[i + 1] = branchT[i]->FirstChildElement("test");//first test node
			decisionNode.push_back(branchT[i]->FirstChildElement("test")->GetText());
			//decision[i]->SetTrueNode(tmpT);
			//decision[i]->SetFalseNode(tmpF);
			branchT[i] = branchT[i]->FirstChildElement("true");
			branchF[i] = branchT[i]->FirstChildElement("false");
			tmpT = nullptr;
			tmpF = nullptr;
		}
		else if (branchT[i]->FirstChild() == branchT[i]->FirstChildElement("action")) {
			
		}


		decision.SetDecision(decisionNode);
		i++;
		counter++;
	}
	while (true) {
		if (branchF[i]->FirstChild() == branchF[i]->FirstChildElement("test")) {
			tmp_decisionNode[i + 1] = branchF[i]->FirstChildElement("test");
		}
		else if (branchF[i]->FirstChild() == branchF[i]->FirstChildElement("test")) {//true branch
			tmp_decisionNode[i + 1] = branchF[i]->FirstChildElement("test");//first test node
			decisionNode.push_back(branchF[i]->FirstChildElement("test")->GetText());
			//decision[i]->SetTrueNode(tmpT);
			//decision[i]->SetFalseNode(tmpF);
			branchT[i] = branchT[i]->FirstChildElement("true");
			branchF[i] = branchT[i]->FirstChildElement("false");
			tmpT = nullptr;
			tmpF = nullptr;
		}
	}


	return decision;
}
