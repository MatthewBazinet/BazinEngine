#include "XMLDecisionTreeReader.h"

DecisionTreeNode XMLDecisionTreeReader::ReadFile(const char* filepath_)
{
	TinyXMLDocument doc;
	doc.LoadFile(filepath_);
	bool status = doc.Error();
	if (status) {
		std::cout << doc.ErrorIDToName(doc.ErrorID()) << std::endl;
	}
	std::vector<XMLElement*> tmp_decisionNode;
	tmp_decisionNode.push_back(doc.FirstChildElement("decisionTree"));
	std::vector<std::string> decisionNode;
	XMLDecision decision;
	std::vector<XMLElement*> branchT;
	std::vector<XMLElement*> branchF;
	DecisionTreeNode* tmpT;
	DecisionTreeNode* tmpF;
	int counter = 1;
	int i = 0;
	if (tmp_decisionNode[i]->FirstChild() == tmp_decisionNode[i]->FirstChildElement("test")) {
		tmp_decisionNode.push_back(tmp_decisionNode[i]->FirstChildElement("test"));//first test node
		decisionNode.push_back("root");
		decisionNode.push_back(tmp_decisionNode[i]->FirstChildElement("test")->GetText());
		//decision[i]->SetTrueNode(tmpT);
		//decision[i]->SetFalseNode(tmpF);
		branchT.push_back(tmp_decisionNode[i]->FirstChildElement("true"));
		branchF.push_back(tmp_decisionNode[i]->FirstChildElement("false"));
		//decisionNode.push_back(branchF[0]->FirstChildElement("test")->GetText());
		tmpT = nullptr;
		tmpF = nullptr;
	}
	i++;
	while (true) {
		if (tmp_decisionNode[i]->FirstChild() == tmp_decisionNode[i]->FirstChildElement("test")) {
			tmp_decisionNode.push_back(tmp_decisionNode[i]->FirstChildElement("test"));//first test node
			decisionNode.push_back(tmp_decisionNode[i]->FirstChildElement("test")->GetText());
			//decision[i]->SetTrueNode(tmpT);
			//decision[i]->SetFalseNode(tmpF);

			branchT.push_back(tmp_decisionNode[i]->FirstChildElement("true"));
			branchF.push_back(tmp_decisionNode[i]->FirstChildElement("false"));

			tmpT = nullptr;
			tmpF = nullptr;
		}else if (branchT[i-1]->FirstChild() == branchT[i-1]->FirstChildElement("test")) {//true branch
			tmp_decisionNode.push_back(branchT[i-1]->FirstChildElement("test"));//first test node
			decisionNode.push_back(branchT[i-1]->FirstChildElement("test")->GetText());
			//decision[i]->SetTrueNode(tmpT);
			//decision[i]->SetFalseNode(tmpF);
			branchT.push_back(branchT[i-1]->FirstChildElement("true"));
			branchF.push_back(branchT[i-1]->FirstChildElement("false"));
			if (branchF[i - 1]->FirstChildElement("test")) {
				tmp_decisionNode.push_back(branchF[i - 1]->FirstChildElement("test"));//first test node
				decisionNode.push_back(branchF[i - 1]->FirstChildElement("test")->GetText());
				//decision[i]->SetTrueNode(tmpT);
				//decision[i]->SetFalseNode(tmpF);
				branchT.push_back(branchF[i - 1]->FirstChildElement("true"));
				branchF.push_back(branchF[i - 1]->FirstChildElement("false"));
			}
			tmpT = nullptr;
			tmpF = nullptr;
		}else if (branchT[i]->FirstChild() == branchT[i]->FirstChildElement("action")) {
			break;
		}
		i++;
		counter++;
	}

	if (branchF[0]->FirstChild() == branchF[0]->FirstChildElement("test")) {
		tmp_decisionNode.push_back(branchF[0]->FirstChildElement("test"));
		decisionNode.push_back(branchF[0]->FirstChildElement("test")->GetText());
		branchT.push_back(branchF[0]->FirstChildElement("true"));
		branchF.push_back(branchF[0]->FirstChildElement("false"));
	}
	i++;
	while (true) {
		if (branchF[i]->FirstChild() == branchF[i]->FirstChildElement("test")) {//true branch
			tmp_decisionNode.push_back(branchF[i-1]->FirstChildElement("test"));//first test node
			decisionNode.push_back(branchF[i]->FirstChildElement("test")->GetText());
			//decision[i]->SetTrueNode(tmpT);
			//decision[i]->SetFalseNode(tmpF);
			branchT.push_back(branchF[i-1]->FirstChildElement("true"));
			branchF.push_back(branchF[i-1]->FirstChildElement("false"));
			tmpT = nullptr;
			tmpF = nullptr;
		}else if (branchF[i]->FirstChild() == branchF[i]->FirstChildElement("action")) {
		break;
		}
		i++;
	}
	decision.SetDecision(decisionNode);

	return decision;
}
