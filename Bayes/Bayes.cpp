// Bayes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;

class LanguageObject
{
public:
	LanguageObject(string val)
	{
		value = val;
	}
	string name;
	string value;
};

class Environment : public LanguageObject
{
public:
	Environment(string val) : LanguageObject( val)
	{
		name = "Environment";
		
	}

};

class Job : public LanguageObject
{
public:
	Job(string val) : LanguageObject(val)
	{
		name = "job";
	
	}
};

class StimulusSituation : public LanguageObject
{
public:
	StimulusSituation(string val) : LanguageObject(val)
	{
		name = "StimulusSituation";

	}
};

class StimulusResponse : public LanguageObject
{
public:
	StimulusResponse(string val) : LanguageObject(val)
	{
		name = "StimulusResponse";

	}
};

class Feedback : public LanguageObject
{
public:

	Feedback(string val) : LanguageObject(val)
	{
		name = "feedback";

	}
};

class Medium : public LanguageObject
{
public:

	Medium(string val) : LanguageObject(val)
	{
		name = "medium";

	}
};



class Semantic
{
public:
	string name;
};

enum LOGICAL_SEMANTIC
{
	IF,OR,AND,ASSIGN
};
class BaseRelation
{
public:
	BaseRelation(){}

	unsigned int object_class = 0;
	unsigned int class_member = 0;
	unsigned int logical_semantic_index = 0;
};

class EquivalenceRelation : public BaseRelation
{
public:
	EquivalenceRelation() : BaseRelation()
	{

	}
	EquivalenceRelation(string Object_class_text, 
						string Class_member_text, 
						string semantic)
		: BaseRelation()
	{
		object_class_text = Object_class_text;
		class_member_text = Class_member_text;
		logical_semantic = semantic;
	}

	string object_class_text;
	string class_member_text;
	string logical_semantic;
};

class EquivalenceIndex : public BaseRelation
{
public:
	EquivalenceIndex() : BaseRelation()
	{

	}

	EquivalenceIndex(unsigned int object_index_id, 
					 unsigned int class_member_id, 
					 unsigned int logical_op_id) 
		: BaseRelation()
	{
		this->class_member = class_member_id;
		this->object_class = object_index_id;
		this->logical_semantic_index = logical_op_id;
	}
};

class BaseRule
{
public:
	BaseRule(){}
};

class Rule : public BaseRule
{
public:
	Rule() : BaseRule()
	{
		consequence.logical_semantic = "assign";
	}
	
	vector<EquivalenceRelation> q;
	EquivalenceRelation consequence;
};

class RuleIndex : public BaseRule
{
public:
	RuleIndex() : BaseRule()
	{
		consequence.logical_semantic_index = LOGICAL_SEMANTIC::ASSIGN;
	}

	vector<EquivalenceIndex> q;
	EquivalenceIndex consequence;
};

class Input
{
public:
	LanguageObject *L;
};

#include <unordered_map>

using std::unordered_map;

int main(int argc, char** argv)
{


	unordered_map<string, int> object_type_indexes;
	object_type_indexes["environment"]= 0;
	object_type_indexes["job"] = 1;
	object_type_indexes["StimulusSituation"] = 2;
	object_type_indexes["StimulusResponse"] = 3;
	object_type_indexes["feedback"] = 4;
	object_type_indexes["medium"] = 5;


	// defining the raw data objects in
	// objects defining their particular ontological role.
	vector<vector<LanguageObject>*> objects;
	
	vector< LanguageObject > env_allowed_values;
	objects.push_back(&env_allowed_values);

	env_allowed_values.push_back(Environment("papers"));
	env_allowed_values.push_back(Environment("manuals"));
	env_allowed_values.push_back(Environment("documents"));
	env_allowed_values.push_back(Environment("textbooks"));
	env_allowed_values.push_back(Environment("pictures"));
	env_allowed_values.push_back(Environment("illustrations"));
	env_allowed_values.push_back(Environment("photographs"));
	env_allowed_values.push_back(Environment("diagrams"));
	env_allowed_values.push_back(Environment("machines"));
	env_allowed_values.push_back(Environment("buildings"));
	env_allowed_values.push_back(Environment("tools"));
	env_allowed_values.push_back(Environment("numbers"));
	env_allowed_values.push_back(Environment("formulas"));
	env_allowed_values.push_back(Environment("computer programs"));

	vector< LanguageObject > job_allowed_values;
	objects.push_back(&job_allowed_values);

	job_allowed_values.push_back(Job("lecturing"));
	job_allowed_values.push_back(Job("advising"));
	job_allowed_values.push_back(Job("counselling"));
	job_allowed_values.push_back(Job("building"));
	job_allowed_values.push_back(Job("repairing"));
	job_allowed_values.push_back(Job("troubleshooting"));
	job_allowed_values.push_back(Job("writing"));
	job_allowed_values.push_back(Job("typing"));
	job_allowed_values.push_back(Job("drawing"));
	job_allowed_values.push_back(Job("evaluating"));
	job_allowed_values.push_back(Job("reasoning"));
	job_allowed_values.push_back(Job("investigating"));

	vector<LanguageObject> stim_situation_allowed_values;
	objects.push_back(&stim_situation_allowed_values);

	stim_situation_allowed_values.push_back(StimulusSituation("verbal"));
	stim_situation_allowed_values.push_back(StimulusSituation("visual"));
	stim_situation_allowed_values.push_back(StimulusSituation("physical object"));
	stim_situation_allowed_values.push_back(StimulusSituation("symbolic"));

	vector <LanguageObject> stim_response_allowed_values;
	objects.push_back(&stim_response_allowed_values);

	stim_response_allowed_values.push_back(StimulusResponse("oral"));
	stim_response_allowed_values.push_back(StimulusResponse("hands-on"));
	stim_response_allowed_values.push_back(StimulusResponse("documented"));
	stim_response_allowed_values.push_back(StimulusResponse("analytical"));

	vector<LanguageObject> feedback;
	objects.push_back(&feedback);

	feedback.push_back(Feedback("required"));
	feedback.push_back(Feedback("not required"));

	vector<LanguageObject> medium;
	objects.push_back(&medium);

	medium.push_back(Medium("workshop"));
	medium.push_back(Medium("lecture-tutorial"));
	medium.push_back(Medium("videocassette"));
	medium.push_back(Medium("role-play exersizes"));





	// defining rule set
	Rule rule_1;

	rule_1.q.push_back(EquivalenceRelation("environment", "papers", "if"));
	rule_1.q.push_back(EquivalenceRelation("environment", "manuals", "or"));
	rule_1.q.push_back(EquivalenceRelation("environment", "textbooks", "or"));
	rule_1.consequence.object_class_text = "StimulusSituation";
	rule_1.consequence.class_member_text = "verbal";

	Rule rule_2;

	rule_2.q.push_back(EquivalenceRelation("environment", "pictures", "if"));
	rule_2.q.push_back(EquivalenceRelation("environment", "illustrations", "or"));
	rule_2.q.push_back(EquivalenceRelation("environment", "photographs", "or"));
	rule_2.q.push_back(EquivalenceRelation("environment", "diagrams", "or"));
	rule_2.consequence.object_class_text = "StimulusSituation";
	rule_2.consequence.class_member_text = "visual";

	Rule rule_3;

	rule_3.q.push_back(EquivalenceRelation("environment", "machines", "if"));
	rule_3.q.push_back(EquivalenceRelation("environment", "buildings", "or"));
	rule_3.q.push_back(EquivalenceRelation("environment", "tools", "or"));
	rule_3.consequence.object_class_text = "StimulusSituation";
	rule_3.consequence.class_member_text = "physical object";

	Rule rule_4;

	rule_4.q.push_back(EquivalenceRelation("environment", "numbers", "if"));
	rule_4.q.push_back(EquivalenceRelation("environment", "formulas", "or"));
	rule_4.q.push_back(EquivalenceRelation("environment", "computer programs", "or"));
	rule_4.consequence.object_class_text = "StimulusSituation";
	rule_4.consequence.class_member_text = "symbolic";


	Rule rule_5;

	rule_5.q.push_back(EquivalenceRelation("job", "lecturing", "if"));
	rule_5.q.push_back(EquivalenceRelation("job", "advising", "or"));
	rule_5.q.push_back(EquivalenceRelation("job", "counselling", "or"));
	rule_5.consequence.object_class_text = "StimulusResponse";
	rule_5.consequence.class_member_text = "oral";

	Rule rule_6;

	rule_6.q.push_back(EquivalenceRelation("job", "building", "if"));
	rule_6.q.push_back(EquivalenceRelation("job", "repairing", "or"));
	rule_6.q.push_back(EquivalenceRelation("job", "troubleshooting", "or"));
	rule_6.consequence.object_class_text = "StimulusResponse";
	rule_6.consequence.class_member_text = "hands-on";

	Rule rule_7;

	rule_7.q.push_back(EquivalenceRelation("job", "writing", "if"));
	rule_7.q.push_back(EquivalenceRelation("job", "typing", "or"));
	rule_7.q.push_back(EquivalenceRelation("job", "drawing", "or"));
	rule_7.consequence.object_class_text = "StimulusResponse";
	rule_7.consequence.class_member_text = "documented";

	Rule rule_8;

	rule_8.q.push_back(EquivalenceRelation("job", "evaluating", "if"));
	rule_8.q.push_back(EquivalenceRelation("job", "reasoning", "or"));
	rule_8.q.push_back(EquivalenceRelation("job", "investigating", "or"));
	rule_8.consequence.object_class_text = "StimulusResponse";
	rule_8.consequence.class_member_text = "analytical";

	Rule rule_9;

	rule_9.q.push_back(EquivalenceRelation("StimulusSituation", "physical object", "if"));
	rule_9.q.push_back(EquivalenceRelation("StimulusResponse", "hands-on", "and"));
	rule_9.q.push_back(EquivalenceRelation("feedback", "required", "and"));
	rule_9.consequence.object_class_text = "medium";
	rule_9.consequence.class_member_text = "workshop";

	Rule rule_10;

	rule_10.q.push_back(EquivalenceRelation("StimulusSituation", "symbolic", "if"));
	rule_10.q.push_back(EquivalenceRelation("StimulusResponse", "analytical", "and"));
	rule_10.q.push_back(EquivalenceRelation("feedback", "required", "and"));
	rule_10.consequence.object_class_text = "medium";
	rule_10.consequence.class_member_text = "lecture-tutorial";

	Rule rule_11;

	rule_11.q.push_back(EquivalenceRelation("StimulusSituation", "visual", "if"));
	rule_11.q.push_back(EquivalenceRelation("StimulusResponse", "documented", "and"));
	rule_11.q.push_back(EquivalenceRelation("feedback", "required", "and"));
	rule_11.consequence.object_class_text = "medium";
	rule_11.consequence.class_member_text = "videocassette";

	Rule rule_12;

	rule_12.q.push_back(EquivalenceRelation("StimulusSituation", "visual", "if"));
	rule_12.q.push_back(EquivalenceRelation("StimulusResponse", "oral", "and"));
	rule_12.q.push_back(EquivalenceRelation("feedback", "required", "and"));
	rule_12.consequence.object_class_text = "medium";
	rule_12.consequence.class_member_text = "lecture-tutorial";

	Rule rule_13;

	rule_13.q.push_back(EquivalenceRelation("StimulusSituation", "verbal", "if"));
	rule_13.q.push_back(EquivalenceRelation("StimulusResponse", "analytical", "and"));
	rule_13.q.push_back(EquivalenceRelation("feedback", "required", "and"));
	rule_13.consequence.object_class_text = "medium";
	rule_13.consequence.class_member_text = "lecture-tutorial";


	Rule rule_14;

	rule_14.q.push_back(EquivalenceRelation("StimulusSituation", "verbal", "if"));
	rule_14.q.push_back(EquivalenceRelation("StimulusResponse", "oral", "and"));
	rule_14.q.push_back(EquivalenceRelation("feedback", "required", "and"));
	rule_14.consequence.object_class_text = "medium";
	rule_14.consequence.class_member_text = "role-play exersizes";

	vector<Rule*> rules;
	rules.push_back(&rule_1);
	rules.push_back(&rule_2);
	rules.push_back(&rule_3);
	rules.push_back(&rule_4);
	rules.push_back(&rule_5);
	rules.push_back(&rule_6);
	rules.push_back(&rule_7);
	rules.push_back(&rule_8);
	rules.push_back(&rule_9);
	rules.push_back(&rule_10);
	rules.push_back(&rule_11);
	rules.push_back(&rule_12);
	rules.push_back(&rule_13);
	rules.push_back(&rule_14);


	// search through the rules and find the strings in
	// the table database, store the integer that indexes each string
	for (int i = 0; i < rules.size(); i++)
	{
		for (int j = 0; j < rules[i]->q.size(); j++)
		{
			int object_class_index = -1;
			for (int k = 0; k < objects.size(); k++)
			{
				if (rules[i]->q[j].object_class_text == (*objects[k])[0].name)
				{
					rules[i]->q[j].object_class = k;
					object_class_index = k;
					break;
				}
			}
			
			for (int c = 0; c < (*objects[rules[i]->q[j].object_class]).size(); c++)
			{
				if (rules[i]->q[j].class_member_text == (*objects[rules[i]->q[j].object_class])[c].value)
				{
					rules[i]->q[j].class_member = c;
					break;
				}
			}
		}

		int object_class_index = -1;
		for (int k = 0; k < objects.size(); k++)
		{
			if (rules[i]->consequence.object_class_text == (*objects[k])[0].name)
			{
				rules[i]->consequence.object_class = k;
				object_class_index = k;
				break;
			}
		}

		for (int c = 0; c < (*objects[rules[i]->consequence.object_class]).size(); c++)
		{
			if (rules[i]->consequence.class_member_text == (*objects[rules[i]->consequence.object_class])[c].value)
			{
				rules[i]->consequence.class_member = c;
				break;
			}
		}
	}

	

	// restore the rule set data relations as integers without strings
	// looking up the strings is a simple task from the objects database.
	vector<RuleIndex*> ruleIndexes;
	for (int i = 0; i < rules.size(); i++)
	{
		RuleIndex *rI = new RuleIndex();
		for (int j = 0; j < rules[i]->q.size(); j++)
		{
			unsigned int semantic = 0;
			if (rules[i]->q[j].logical_semantic == "if")
			{
				semantic = LOGICAL_SEMANTIC::IF;
			}
			else if (rules[i]->q[j].logical_semantic == "or")
			{
				semantic = LOGICAL_SEMANTIC::OR;
			}
			else if (rules[i]->q[j].logical_semantic == "and")
			{
				semantic = LOGICAL_SEMANTIC::AND;
			}
			else if (rules[i]->q[j].logical_semantic == "assign")
			{
				semantic = LOGICAL_SEMANTIC::ASSIGN;
			}
			unsigned int c_m = rules[i]->q[j].class_member;
			unsigned int o_c = rules[i]->q[j].object_class;
			
			rI->q.push_back(EquivalenceIndex(o_c, c_m, semantic));
		}
		
		rI->consequence.object_class = rules[i]->consequence.object_class;
		rI->consequence.class_member = rules[i]->consequence.class_member;
		rI->consequence.logical_semantic_index = LOGICAL_SEMANTIC::ASSIGN;
	
		ruleIndexes.push_back(rI);
	}

	string semantics[4] = { "if", "or", "and", "assign" };

	// print the rules set using the indexes and looking up the 
	// strings from the objects database
	for (int i = 0; i < ruleIndexes.size(); i++)
	{
		cout << "**********************************************" << endl;
		cout << "Rule " << i + 1 << endl;
		cout << "**********************************************" << endl;
		for (int j = 0; j < ruleIndexes[i]->q.size(); j++)
		{

			string statement = "";
			statement += semantics[ ruleIndexes[i]->q[j].logical_semantic_index ];
			statement += " ";
			int table_index = ruleIndexes[i]->q[j].object_class;
			int member_index = ruleIndexes[i]->q[j].class_member;

			statement += (*objects[table_index])[member_index].name;
			statement += " is ";
			statement += (*objects[table_index])[member_index].value;

			cout << statement << endl;
		}
		int table_index = ruleIndexes[i]->consequence.object_class;
		int member_index = ruleIndexes[i]->consequence.class_member;

		cout << "then " << (*objects[table_index])[member_index].name;
		cout << " is " << (*objects[table_index])[member_index].value << endl;

		cout << endl;


	}

	string environment_type = "machines";
	int query_object = object_type_indexes["environment"];

	int stim_sit_output = 0;
	
	for (int i = 0; i < ruleIndexes.size(); i++)
	{
		bool ruleSet = false;
		
		for (int j = 0; j < ruleIndexes[i]->q.size(); j++)
		{
			if (ruleIndexes[i]->q[j].object_class == query_object)
			{
				for (int k = 0; k < (*objects[query_object]).size(); k++)
				{
					if (environment_type == (*objects[query_object])[k].value) 
 					{
						ruleSet = true;
						if (ruleIndexes[i]->q[j].logical_semantic_index == LOGICAL_SEMANTIC::OR)
							break;
						if (ruleIndexes[i]->q[j].logical_semantic_index == LOGICAL_SEMANTIC::IF)
							break;
					}
				}
			}
			if (ruleSet) break;
		}
		if (ruleSet == true)
		{
			stim_sit_output = ruleIndexes[i]->consequence.class_member;
		}
	}
	
	string job_type = "repairing";
	query_object = object_type_indexes["job"];

	int stim_res_output = 0;

	for (int i = 0; i < ruleIndexes.size(); i++)
	{
		bool ruleSet = false;

		for (int j = 0; j < ruleIndexes[i]->q.size(); j++)
		{
			if (ruleIndexes[i]->q[j].object_class == query_object)
			{
				for (int k = 0; k < (*objects[query_object]).size(); k++)
				{
					if (job_type == (*objects[query_object])[k].value)
					{
						ruleSet = true;
						if (ruleIndexes[i]->q[j].logical_semantic_index == LOGICAL_SEMANTIC::OR)
							break;
						if (ruleIndexes[i]->q[j].logical_semantic_index == LOGICAL_SEMANTIC::IF)
							break;
					}
				}
				
			}
			if (ruleSet) break;
		}
		if (ruleSet == true)
		{
			stim_res_output = ruleIndexes[i]->consequence.class_member;
		}
	}



	//query_object = object_type_indexes["medium"];
	query_object = object_type_indexes["StimulusSituation"];
	

	int medium_output = 0;

	for (int i = 0; i < ruleIndexes.size(); i++)
	{
		bool ruleSet = false;
		bool rulePart1 = false;

		for (int j = 0; j < ruleIndexes[i]->q.size(); j++)
		{
			if (rulePart1 == false)
			{

			
				if (ruleIndexes[i]->q[j].object_class == query_object)
				{
					if (stim_sit_output == ruleIndexes[i]->q[j].class_member)
						{
							rulePart1 = true;
							query_object = object_type_indexes["StimulusResponse"];
							if (ruleIndexes[i]->q[j].logical_semantic_index == LOGICAL_SEMANTIC::IF)
								break;
						}
				
				
				}
			}
			else
			{
				
				if (ruleIndexes[i]->q[j].object_class == query_object)
				{
					if (stim_res_output == ruleIndexes[i]->q[j].class_member)
					{
						ruleSet = true;
						if (ruleIndexes[i]->q[j].logical_semantic_index == LOGICAL_SEMANTIC::IF)
							break;
					}


				}
			}
			
		}
		if (ruleSet == true)
		{
			medium_output = ruleIndexes[i]->consequence.class_member;
		}
	}

	cout << "TEST WITH ... 1) Environment is workshop, 2) job is repairing 3) feedback assumed" << endl;
	cout << "medium output is " << (*objects[object_type_indexes["medium"]])[medium_output].value << endl << endl;

	//InputQuery input;
	//input.q.push_back(EquivalenceRelation("machines"))





	return 0;
}

