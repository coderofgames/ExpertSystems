// Bayes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "matrix_solver.h"
#include "Timer.h"
#include <thread>
#include <future> 
#include <mutex>
#include <functional>
#include <conio.h>

#include "windows.h"
#include "winuser.h"



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

namespace EXPERT_VERSION_1
{
	unordered_map<string, int> object_type_indexes;
	vector<vector<LanguageObject>*> objects;

	vector<Rule*> rules;

	vector <LanguageObject> env_allowed_values;
	vector <LanguageObject> job_allowed_values;
	vector <LanguageObject> stim_situation_allowed_values;
	vector <LanguageObject> stim_response_allowed_values;
	vector <LanguageObject> feedback;
	vector <LanguageObject> medium;
	

	vector<RuleIndex*> ruleIndexes;

	Rule rule_1, rule_2, rule_3, rule_4, rule_5, rule_6, rule_7, rule_8, rule_9, rule_10, rule_11, rule_12, rule_13, rule_14;

	void Initialize_Object_Type_Map()
	{
		object_type_indexes["environment"] = 0;
		object_type_indexes["job"] = 1;
		object_type_indexes["StimulusSituation"] = 2;
		object_type_indexes["StimulusResponse"] = 3;
		object_type_indexes["feedback"] = 4;
		object_type_indexes["medium"] = 5;
	}

	void Initialize_Objects_Database()
	{
		
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
		objects.push_back(&env_allowed_values);

		
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
		objects.push_back(&job_allowed_values);

		
		stim_situation_allowed_values.push_back(StimulusSituation("verbal"));
		stim_situation_allowed_values.push_back(StimulusSituation("visual"));
		stim_situation_allowed_values.push_back(StimulusSituation("physical object"));
		stim_situation_allowed_values.push_back(StimulusSituation("symbolic"));
		objects.push_back(&stim_situation_allowed_values);

		
		stim_response_allowed_values.push_back(StimulusResponse("oral"));
		stim_response_allowed_values.push_back(StimulusResponse("hands-on"));
		stim_response_allowed_values.push_back(StimulusResponse("documented"));
		stim_response_allowed_values.push_back(StimulusResponse("analytical"));
		objects.push_back(&stim_response_allowed_values);

		
		feedback.push_back(Feedback("required"));
		feedback.push_back(Feedback("not required"));
		objects.push_back(&feedback);

		
		medium.push_back(Medium("workshop"));
		medium.push_back(Medium("lecture-tutorial"));
		medium.push_back(Medium("videocassette"));
		medium.push_back(Medium("role-play exersizes"));
		objects.push_back(&medium);
	}

	void Initialize_Rules()
	{
		// defining rule set
		//Rule rule_1;

		rule_1.q.push_back(EquivalenceRelation("environment", "papers", "if"));
		rule_1.q.push_back(EquivalenceRelation("environment", "manuals", "or"));
		rule_1.q.push_back(EquivalenceRelation("environment", "textbooks", "or"));
		rule_1.consequence.object_class_text = "StimulusSituation";
		rule_1.consequence.class_member_text = "verbal";

		//Rule rule_2;

		rule_2.q.push_back(EquivalenceRelation("environment", "pictures", "if"));
		rule_2.q.push_back(EquivalenceRelation("environment", "illustrations", "or"));
		rule_2.q.push_back(EquivalenceRelation("environment", "photographs", "or"));
		rule_2.q.push_back(EquivalenceRelation("environment", "diagrams", "or"));
		rule_2.consequence.object_class_text = "StimulusSituation";
		rule_2.consequence.class_member_text = "visual";

		//Rule rule_3;

		rule_3.q.push_back(EquivalenceRelation("environment", "machines", "if"));
		rule_3.q.push_back(EquivalenceRelation("environment", "buildings", "or"));
		rule_3.q.push_back(EquivalenceRelation("environment", "tools", "or"));
		rule_3.consequence.object_class_text = "StimulusSituation";
		rule_3.consequence.class_member_text = "physical object";

		//Rule rule_4;

		rule_4.q.push_back(EquivalenceRelation("environment", "numbers", "if"));
		rule_4.q.push_back(EquivalenceRelation("environment", "formulas", "or"));
		rule_4.q.push_back(EquivalenceRelation("environment", "computer programs", "or"));
		rule_4.consequence.object_class_text = "StimulusSituation";
		rule_4.consequence.class_member_text = "symbolic";


		//Rule rule_5;

		rule_5.q.push_back(EquivalenceRelation("job", "lecturing", "if"));
		rule_5.q.push_back(EquivalenceRelation("job", "advising", "or"));
		rule_5.q.push_back(EquivalenceRelation("job", "counselling", "or"));
		rule_5.consequence.object_class_text = "StimulusResponse";
		rule_5.consequence.class_member_text = "oral";

		//Rule rule_6;

		rule_6.q.push_back(EquivalenceRelation("job", "building", "if"));
		rule_6.q.push_back(EquivalenceRelation("job", "repairing", "or"));
		rule_6.q.push_back(EquivalenceRelation("job", "troubleshooting", "or"));
		rule_6.consequence.object_class_text = "StimulusResponse";
		rule_6.consequence.class_member_text = "hands-on";

		//Rule rule_7;

		rule_7.q.push_back(EquivalenceRelation("job", "writing", "if"));
		rule_7.q.push_back(EquivalenceRelation("job", "typing", "or"));
		rule_7.q.push_back(EquivalenceRelation("job", "drawing", "or"));
		rule_7.consequence.object_class_text = "StimulusResponse";
		rule_7.consequence.class_member_text = "documented";

		//Rule rule_8;

		rule_8.q.push_back(EquivalenceRelation("job", "evaluating", "if"));
		rule_8.q.push_back(EquivalenceRelation("job", "reasoning", "or"));
		rule_8.q.push_back(EquivalenceRelation("job", "investigating", "or"));
		rule_8.consequence.object_class_text = "StimulusResponse";
		rule_8.consequence.class_member_text = "analytical";

		//Rule rule_9;

		rule_9.q.push_back(EquivalenceRelation("StimulusSituation", "physical object", "if"));
		rule_9.q.push_back(EquivalenceRelation("StimulusResponse", "hands-on", "and"));
		rule_9.q.push_back(EquivalenceRelation("feedback", "required", "and"));
		rule_9.consequence.object_class_text = "medium";
		rule_9.consequence.class_member_text = "workshop";

		//Rule rule_10;

		rule_10.q.push_back(EquivalenceRelation("StimulusSituation", "symbolic", "if"));
		rule_10.q.push_back(EquivalenceRelation("StimulusResponse", "analytical", "and"));
		rule_10.q.push_back(EquivalenceRelation("feedback", "required", "and"));
		rule_10.consequence.object_class_text = "medium";
		rule_10.consequence.class_member_text = "lecture-tutorial";

		//Rule rule_11;

		rule_11.q.push_back(EquivalenceRelation("StimulusSituation", "visual", "if"));
		rule_11.q.push_back(EquivalenceRelation("StimulusResponse", "documented", "and"));
		rule_11.q.push_back(EquivalenceRelation("feedback", "required", "and"));
		rule_11.consequence.object_class_text = "medium";
		rule_11.consequence.class_member_text = "videocassette";

		//Rule rule_12;

		rule_12.q.push_back(EquivalenceRelation("StimulusSituation", "visual", "if"));
		rule_12.q.push_back(EquivalenceRelation("StimulusResponse", "oral", "and"));
		rule_12.q.push_back(EquivalenceRelation("feedback", "required", "and"));
		rule_12.consequence.object_class_text = "medium";
		rule_12.consequence.class_member_text = "lecture-tutorial";

		//Rule rule_13;

		rule_13.q.push_back(EquivalenceRelation("StimulusSituation", "verbal", "if"));
		rule_13.q.push_back(EquivalenceRelation("StimulusResponse", "analytical", "and"));
		rule_13.q.push_back(EquivalenceRelation("feedback", "required", "and"));
		rule_13.consequence.object_class_text = "medium";
		rule_13.consequence.class_member_text = "lecture-tutorial";


		//Rule rule_14;

		rule_14.q.push_back(EquivalenceRelation("StimulusSituation", "verbal", "if"));
		rule_14.q.push_back(EquivalenceRelation("StimulusResponse", "oral", "and"));
		rule_14.q.push_back(EquivalenceRelation("feedback", "required", "and"));
		rule_14.consequence.object_class_text = "medium";
		rule_14.consequence.class_member_text = "role-play exersizes";


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

	}

	void Convert_Rules_To_Indexes()
	{
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
	}

	string semantics[4] = { "if", "or", "and", "assign" };

	void Print_Individual_Rule(int i)
	{

		cout << "**********************************************" << endl;
		cout << "Rule " << i + 1 << endl;
		cout << "**********************************************" << endl;
		for (int j = 0; j < ruleIndexes[i]->q.size(); j++)
		{

			string statement = "";
			statement += semantics[ruleIndexes[i]->q[j].logical_semantic_index];
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

	void Print_Rules()
	{
		
		// print the rules set using the indexes and looking up the 
		// strings from the objects database
		for (int i = 0; i < ruleIndexes.size(); i++)
		{
			Print_Individual_Rule(i);
		}
	}

	void Cleanup()
	{
		for (int q = 0; q < ruleIndexes.size(); q++)
			delete ruleIndexes[q];

	}

	void RunExample()
	{
	
		Initialize_Object_Type_Map();
		Initialize_Objects_Database();
		Initialize_Rules();
		Convert_Rules_To_Indexes();
		Print_Rules();


		cout << "TEST WITH ... 1) Environment is machines, 2) job is repairing 3) feedback assumed" << endl;
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
					int index = -1;
					for (int k = 0; k < (*objects[query_object]).size(); k++)
					{
						if (environment_type == (*objects[query_object])[k].value) 
 						{
						
							index = k;
							break;
						}
					}
					if (index != -1)
					{
						if( ruleIndexes[i]->q[j].class_member == index )
							ruleSet = true;
					}
				}
				if (ruleSet) break;
			}
			if (ruleSet == true)
			{
				stim_sit_output = ruleIndexes[i]->consequence.class_member;

				Print_Individual_Rule(i);
				break;
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
					int index = -1;
					for (int k = 0; k < (*objects[query_object]).size(); k++)
					{
						if (job_type == (*objects[query_object])[k].value)
						{
							index = k;
							break;
						}
					}
					if (index != -1)
					{
						if (ruleIndexes[i]->q[j].class_member == index)
							ruleSet = true;
					}
				
				}
				if (ruleSet) break;
			}
			if (ruleSet == true)
			{
				stim_res_output = ruleIndexes[i]->consequence.class_member;
				Print_Individual_Rule(i);
				break;
			}
		}



		//query_object = object_type_indexes["medium"];
		query_object = object_type_indexes["StimulusSituation"];
	

		int medium_output = 0;
		bool ruleSet = false;
		bool rulePart1 = false; 
		for (int i = 0; i < ruleIndexes.size(); i++)
		{


			for (int j = 0; j < ruleIndexes[i]->q.size(); j++)
			{
				if (rulePart1 == false)
				{

					int index = -1;
					if (ruleIndexes[i]->q[j].object_class == query_object)
					{
						if (stim_sit_output == ruleIndexes[i]->q[j].class_member)
							{
							
								query_object = object_type_indexes["StimulusResponse"];
								//if (ruleIndexes[i]->q[j].logical_semantic_index == LOGICAL_SEMANTIC::IF)
								//	break;
								rulePart1 = true;
							//	break;
							}
				
				
					}
				}
				else
				{
					int index = -1;
					if (ruleIndexes[i]->q[j].object_class == query_object)
					{
						if (stim_res_output == ruleIndexes[i]->q[j].class_member)
						{
							ruleSet = true;
							//if (ruleIndexes[i]->q[j].logical_semantic_index == LOGICAL_SEMANTIC::IF)
								break;
						}


					}
				}
				if (ruleSet == true) break;
			
			}
			if (ruleSet == true)
			{
				medium_output = ruleIndexes[i]->consequence.class_member;
				Print_Individual_Rule(i);
				break;
			}
		}

	
		cout << "medium output is " << (*objects[object_type_indexes["medium"]])[medium_output].value << endl << endl;

		//InputQuery input;
		//input.q.push_back(EquivalenceRelation("machines"))

		Cleanup();
	
	}
	
}

namespace STATE_MACHINE
{
	namespace TEST_STATES
	{
		enum STATES { START_STATE, MIDDLE_STATE, END_STATE };
		string STRING_STATES[3] = { "START_STATE", "MIDDLE_STATE", "END_STATE" };
		enum EVENTS { EVENT_1, EVENT_2, EVENT_3, EVENT_4, EVENT_5, EVENT_6 };
		string string_events[6] = { "EVENT_1", "EVENT_2", "EVENT_3", "EVENT_4", "EVENT_5", "EVENT_6" };
		int transitions[7] = { EVENT_1, EVENT_4, EVENT_2, EVENT_5, EVENT_3, EVENT_6, EVENT_2 };

	};


	

	namespace LINKED_STATE_MACHINE
	{
		using namespace TEST_STATES;

		class State;
		class Transition;

		class Signal
		{
		public:
			Signal(int signal_id)
			{
				id = signal_id;
			}
			int id;
		};
		
		class Transition
		{
		public:
			Transition(State *From, State *To, int signal)
			{
				from = From;
				to = To;
				next = this;
				prev = this;
				signal_id = signal;
			}

			State* Fire_(int signal)
			{
				if (signal == signal_id)
				{
					return to;
				}

				return from;
			}

			int signal_id;
			State *from;
			State *to;
			Transition *next = 0;
			Transition *prev = 0;
		};

		class State
		{
		public:
			int m_id = -1;
			State(int id)
			{
				m_id = id;
			}
			State *Activate(Signal *c)
			{
				State* output = this;
				Transition* temp = m_start;
				while (temp)
				{
					output = temp->Fire_(c->id);
					if (output != this)
						return output;
					temp = temp->next;
					if (temp == m_start)
						break;
				}
				return output;
			}

			Transition* AddTransition(State* p, Signal *c)
			{
				Transition *pNewTransition = new Transition(this, p, c->id);

				if (m_start)
				{
					Transition *temp = m_start;
					Transition *prev = m_start->prev;
				
					if (prev != temp)
					{
						prev->next = pNewTransition;
						temp->prev = pNewTransition;
						pNewTransition->next = temp;
						pNewTransition->prev = prev;
					}
					else
					{
						temp->next = pNewTransition;
						pNewTransition->next = temp;
						temp->prev = pNewTransition;
						pNewTransition->prev = temp;
					}
				}
				else
				{
					m_start = pNewTransition;
					
				}

				return pNewTransition;
			}
			
			
			Transition *m_start = 0;
		};

		class StateMachine
		{
		public:

			State* ProcessEvent(Signal *evt)
			{
				//if (m_current_State >= 0 && m_current_State < m_states.size())
				m_current_State = m_current_State->Activate(evt);

				return m_current_State;
			}
			State* GetCurrentState()
			{
				return m_current_State;
			}
			void SetStartState(State* start)
			{
				m_current_State = start;
			}

			State* m_current_State = 0;
			vector<State*> m_states;
		};

		void RunTest()
		{
			cout << endl;
			cout << "****************************************************" << endl;

			State start_state(START_STATE);
			State middle_state(MIDDLE_STATE);
			State end_state(END_STATE);

			Signal s1(EVENT_1);
			Signal s2(EVENT_2);
			Signal s3(EVENT_3);
			Signal s4(EVENT_4);
			Signal s5(EVENT_5);
			Signal s6(EVENT_6);

			start_state.AddTransition(&middle_state, &s1);
			start_state.AddTransition(&end_state, &s2);

			middle_state.AddTransition(&end_state, &s3);
			middle_state.AddTransition(&start_state, &s4);

			end_state.AddTransition(&middle_state, &s5);
			end_state.AddTransition(&start_state, &s6);

			StateMachine m;
			m.SetStartState(&start_state);

			Signal *state_events[6] = { &s1, &s2, &s3, &s4, &s5, &s6 };


			for (int i = 0; i < 7; i++)
			{
				cout << "State machine current state:   ";
				State* st = m.GetCurrentState();

				switch (STATES(st->m_id))
				{
				case STATES::START_STATE:
					cout << "START_STATE" << endl;
					break;
				case STATES::MIDDLE_STATE:
					cout << "MIDDLE_STATE" << endl;
					break;
				case STATES::END_STATE:
					cout << "END_STATE" << endl;
					break;
				default:
					break;
				};
				cout << "performing transition: " << string_events[transitions[i]] << endl;
				st = m.ProcessEvent(state_events[transitions[i]]);
				//state_machine.stateTransition(transitions[i]);
			}
		}


	};



	namespace VECTOR_STATE_MACHINE
	{
		using namespace TEST_STATES;

		class State;
		class Transition;

#include <chrono>

		// stack overflow
		//http://stackoverflow.com/questions/32693103/threaded-timer-interrupting-a-sleep-stopping-it
		class ThreadTimer
		{
		public:

			ThreadTimer() {}

			~ThreadTimer()
			{
				Stop();
			}

			void Start(std::chrono::milliseconds const & interval,
				std::function<void(void)> const & callback)
			{
				Stop();

				{
					auto locked = std::unique_lock<std::mutex>(mutex);
					stop = false;
				}

				thread = std::thread([=]()
				{
					auto locked = std::unique_lock<std::mutex>(mutex);

					while (!stop) // We hold the mutex that protects stop
					{
						auto result = terminate.wait_for(locked, interval);

						if (result == std::cv_status::timeout)
						{
							callback();
						}
					}
				});
			}

			void Stop()
			{
				{
					// Set the predicate
					auto locked = std::unique_lock<std::mutex>(mutex);
					stop = true;
				}

				// Tell the thread the predicate has changed
				terminate.notify_one();

				if (thread.joinable())
				{
					thread.join();
				}
			}

		private:

			bool stop; // This is the thing the thread is waiting for
			std::thread thread;
			std::mutex mutex;
			std::condition_variable terminate;
		};





		class Signal
		{
		public:
			Signal(int signal_id)
			{
				id = signal_id;
			}
			int id;
		};

		class Transition
		{
		public:
			Transition(State *From, State *To, int signal)
			{
				from = From;
				to = To;
				signal_id = signal;
			}

			State* Fire_(Signal* signal)
			{
				if (signal_id == signal->id)
				{
					return to;
				}

				return from;
			}

			int signal_id;
			State *from;
			State *to;

		};

		class MessagePrint
		{
		public:
			void PrintMessage()
			{
				for (string str : message_lines)
				{
					cout << str << endl;
				}
			}
			MessagePrint* AddLine(string newline)
			{
				message_lines.push_back(newline);
				return this;
			}
			vector<string> message_lines;
		};

		
		

		class InputProcessor
		{
		public:
			std::mutex m_mut;
			void AddBinding(char c, Signal *s)
			{
				m_input_signal_map[c] = s;
				user_inputs.push_back(c);
			}
			void AddBinding(char c, Signal *s, string text)
			{
				m_input_signal_map[c] = s;
				user_inputs.push_back(c);
				m_input_text_map[c] = text;
			}



			Signal*  GetInput()
			{
				static int delay = 0;
				char c = 0;
				
				//cin >> c;
				if (delay == 0)
				{
			

					for (char a : user_inputs)
					{
						
						unsigned short key_state = GetKeyState((unsigned short)a);

						if ((key_state & 0xff) && key_state >> 8)
						{
							delay++;
							return  m_input_signal_map[a];
							

						}
					}
				}
				else
				{
					delay++;
					if (delay == 300000)
						delay = 0;
				}
				return 0;
			}

			bool keyHit = false;
			void SetHitKey(bool val)
			{
				keyHit = val;
			}

			Signal* Process(bool needPrint)
			{
				//cout << endl;c
				//cout << "Enter an option" << endl;
				if (needPrint)
				{
				for (char a : user_inputs)
				{
					if (m_input_text_map.bucket_count()!=0)
						cout << a << ": " << m_input_text_map[a] << endl;
					else
					{
						cout << a << endl;
					}
				}
				}
				Signal* s = 0;
				
				//future<Signal*> f1 = async( &VECTOR_STATE_MACHINE::InputProcessor::GetInput, this);
				return GetInput();

				//return (Signal*)f2.get();

			}

			vector< char > user_inputs;
			unordered_map <char, Signal*> m_input_signal_map;
			unordered_map <char, string> m_input_text_map;
		};

		class StateProcessObject
		{
		public:
			virtual Signal* Process(bool needPrint) = 0;
			virtual void SetHitKey(bool val) = 0;
		};

		class StateProcessImpl : public StateProcessObject
		{
		public:

			Signal* Process(bool needPrint)
			{
				if (needPrint)
				{ 

					if (m_message)	
					{
						m_message->PrintMessage();
					}
				}
				if (inputs)
				{
					Signal *s = inputs->Process(needPrint);
					if (s != 0)
					{
						return s;
					}
				}
				
				return 0;
			}

			StateProcessObject* AddTextLine(string line)
			{
				if (!m_message)
					m_message = new MessagePrint();
				
				m_message->AddLine(line);
				return (StateProcessObject*)this;

			}

			StateProcessObject* AddInputOption(char c, Signal *s)
			{
				if ( inputs == 0 )
					inputs = new InputProcessor();

				inputs->AddBinding(c, s);
				return (StateProcessObject*)this;
			}
			StateProcessObject* AddInputOption(char c, Signal *s, string text)
			{
				if (inputs == 0)
					inputs = new InputProcessor();

				inputs->AddBinding(c, s, text);
				return (StateProcessObject*)this;
			}

			void SetHitKey(bool val)
			{
				if (inputs) inputs->SetHitKey(val);
			}

			StateProcessImpl()
			{

			}
			~StateProcessImpl()
			{
				if (m_message)
					delete m_message;
				if (inputs)
					delete inputs;
			}

			MessagePrint *m_message = 0;
			InputProcessor *inputs = 0;


			
		};

		class State
		{
		public:
			int m_id = -1;

			State(int id)
			{
				m_id = id;
				
			}
			~State()
			{
				
			}

			void SetStateProcessObject(StateProcessObject* obj)
			{
				this->m_stateProcessObject = obj;
			}

			StateProcessObject *GetStateProcessObject()
			{
				return m_stateProcessObject;
			}

			void OnActivate()
			{
				bActivateTimeout = false;
				total_time = 0.0;
				needPrint = true;
				if (timeout)
				{ 
					timer = std::make_unique<ThreadTimer>();
					timer->Start(std::chrono::milliseconds((long long)m_stopTime), std::bind(&State::Callback, this));
				}
			}

			void OnDeactivate()
			{
				//delete timer;
				timer.reset();
				total_time = 0.0;
				needPrint = false; 
			}

			bool needPrint = true;

			State* Process()
			{
				Signal *s = 0;
				
				if (m_stateProcessObject)
				{
					s = m_stateProcessObject->Process(needPrint);

					if (needPrint)
						needPrint = false;
				}
			
				if (bActivateTimeout)
				{
					{
						timer->Stop();
						return Activate(timeout);
					}
				}

				if (s) return Activate(s);

				return this;

			}



			State *Activate(Signal *c)
			{
				State* output = this;
				for (const auto& l : m_tr_list) {
					output = l->Fire_(c);
					if (output != this)
					{
						this->OnDeactivate();
						output->OnActivate();
						
						return output;
					}
				}
				
				return this;
			}

			Transition* AddTransition(State* p, Signal *c)
			{
				Transition *pNewTransition = new Transition(this, p, c->id);
				m_tr_list.push_back(pNewTransition);

				return pNewTransition;
			}

			void AddTimeout(double stopTime, State* timeoutState)
			{
				timeout = new Signal(-10000);
				AddTransition(timeoutState, timeout);

				m_stopTime = stopTime;
			}

			void Callback()
			{
				bActivateTimeout = true;
			}

			std::unique_ptr<ThreadTimer>  timer;// = 0;

			vector< Transition* > m_tr_list;
			double m_stopTime = 0.0;
			Signal *timeout = 0;
			
			double total_time;
			bool bActivateTimeout = false;
			

			StateProcessObject *m_stateProcessObject =0;

		};





		class StateMachine
		{
		public:


			StateMachine()
			{
			}

			void Process(double dt)
			{
				m_next_State = m_current_State->Process();
				if (m_next_State != 0 && m_next_State != m_current_State)
				{
					m_current_State = m_next_State;
				}
			}


			State* ProcessEvent(Signal *evt)
			{
				m_current_State = m_current_State->Activate(evt);

				return m_current_State;
			}
			State* GetCurrentState()
			{
				return m_current_State;
			}
			void SetStartState(State* start)
			{
				m_current_State = start;
			}

			State* m_current_State = 0;
			State* m_next_State = 0;
		};



		void RunTest()
		{
			cout << endl;
			cout << "****************************************************" << endl;

			State start_state(START_STATE);
			State middle_state(MIDDLE_STATE);
			State end_state(END_STATE);

			Signal s1(EVENT_1);
			Signal s2(EVENT_2);
			Signal s3(EVENT_3);
			Signal s4(EVENT_4);
			Signal s5(EVENT_5);
			Signal s6(EVENT_6);

			start_state.AddTransition(&middle_state, &s1);
			start_state.AddTransition(&end_state, &s2);

			middle_state.AddTransition(&end_state, &s3);
			middle_state.AddTransition(&start_state, &s4);

			end_state.AddTransition(&middle_state, &s5);
			end_state.AddTransition(&start_state, &s6);

			StateMachine m;
			m.SetStartState(&start_state);

			Signal *state_events[6] = { &s1, &s2, &s3, &s4, &s5, &s6 };


			for (int i = 0; i < 7; i++)
			{
				cout << "State machine current state:   ";
				State* st = m.GetCurrentState();

				switch (STATES(st->m_id))
				{
				case STATES::START_STATE:
					cout << "START_STATE" << endl;
					break;
				case STATES::MIDDLE_STATE:
					cout << "MIDDLE_STATE" << endl;
					break;
				case STATES::END_STATE:
					cout << "END_STATE" << endl;
					break;
				default:
					break;
				};
				cout << "performing transition: " << string_events[transitions[i]] << endl;
				st = m.ProcessEvent(state_events[transitions[i]]);
				//state_machine.stateTransition(transitions[i]);
			}
		}
		void RunTest3()
		{
			enum TEST_STATES_2 { SELECT_OPTION, 
								VIEW_BALANCE, 
								WITHDRAW_CASH, 
								PRINT_STATEMENT, 
								MORE_TIME, 
								MORE_TIME_WITHDRAW,
								ANOTHER_SERVICE,
								EMIT_10,
								EMIT_20,
								EMIT_50,
								EMIT_OTHER,
								RETURN_CARD };

			string state_names[12]={
				"SELECT_OPTION",
				"VIEW_BALANCE",
				"WITHDRAW_CASH",
				"PRINT_STATEMENT",
				"MORE_TIME",
				"MORE_TIME_WITHDRAW"
				"ANOTHER_SERVICE",
				"EMIT_10",
				"EMIT_20",
				"EMIT_50",
				"EMIT_OTHER",
				"RETURN_CARD"
			};
			Signal s1(1);
			Signal s2(2);
			Signal s3(3);
			Signal s4(4);
			Signal s5(5);
			Signal s6(6);
			Signal s7(7);
			Signal s8(8);
			Signal s9(9);
			Signal s10(10);

			State select_option(SELECT_OPTION);
			State view_balance(VIEW_BALANCE);
			State withdraw_cash(WITHDRAW_CASH);
			State print_statement(PRINT_STATEMENT);
			State more_time(MORE_TIME);
			State more_time_withdraw(MORE_TIME_WITHDRAW);
			State another_service(ANOTHER_SERVICE);
			State emit_10(EMIT_10);
			State emit_20(EMIT_20);
			State emit_50(EMIT_50);
			State emit_other(EMIT_OTHER);
			State return_card(RETURN_CARD);

			select_option.AddTransition(&view_balance, &s1);
			select_option.AddTransition(&withdraw_cash, &s2);
			select_option.AddTransition(&print_statement, &s3);
			StateProcessImpl select_option_obj;
			select_option_obj.AddTextLine("Select an option");
			select_option_obj.AddInputOption('1', &s1, "View Balance");
			select_option_obj.AddInputOption('2', &s2, "Withdraw Cash");
			select_option_obj.AddInputOption('3', &s3, "Print Statement");
			select_option.SetStateProcessObject((StateProcessObject*)&select_option_obj);
			select_option.AddTimeout(5000, &more_time);

			more_time.AddTransition(&select_option, &s3);
			more_time.AddTransition(&return_card, &s4);
			StateProcessImpl more_time_obj;
			more_time_obj.AddTextLine("Would you like More Time? ");
			more_time_obj.AddInputOption('1', &s3, "yes");
			more_time_obj.AddInputOption('2', &s4, "no");
			more_time.SetStateProcessObject((StateProcessObject*)&more_time_obj);

			more_time_withdraw.AddTransition(&withdraw_cash, &s3);
			more_time_withdraw.AddTransition(&return_card, &s4);
			StateProcessImpl more_time_withdraw_obj;
			more_time_withdraw_obj.AddTextLine("Would you like More Time? ");
			more_time_withdraw_obj.AddInputOption('1', &s3, "yes");
			more_time_withdraw_obj.AddInputOption('2', &s4, "no");
			more_time_withdraw.SetStateProcessObject((StateProcessObject*)&more_time_withdraw_obj);

			view_balance.AddTransition(&select_option, &s3);
			view_balance.AddTransition(&return_card, &s4);
			StateProcessImpl view_balance_obj;
			view_balance_obj.AddTextLine("Your balance is *database lookup* ");
			view_balance_obj.AddTextLine("Would you like another service? ");
			view_balance_obj.AddInputOption('1', &s3, "yes");
			view_balance_obj.AddInputOption('2', &s4, "no");
			view_balance.SetStateProcessObject((StateProcessObject*)&view_balance_obj);
			//front_left.AddTimeout(5, &enter);

			print_statement.AddTransition(&select_option, &s3);
			print_statement.AddTransition(&return_card, &s4);
			StateProcessImpl print_statement_obj;
			print_statement_obj.AddTextLine("System prints balance statement *database lookup* ");
			print_statement_obj.AddTextLine("Would you like another service? ");
			print_statement_obj.AddInputOption('1', &s3, "yes");
			print_statement_obj.AddInputOption('2', &s4, "no");
			print_statement.SetStateProcessObject((StateProcessObject*)&print_statement_obj);

			//front_right.AddTransition(&center_right, &s5);
			StateProcessImpl return_card_obj;
			return_card_obj.AddTextLine("Please take your card!");
			return_card_obj.AddTextLine("have a great day!");
			return_card.SetStateProcessObject((StateProcessObject*)&return_card_obj);
			
			
			withdraw_cash.AddTransition(&emit_10, &s3);
			withdraw_cash.AddTransition(&emit_20, &s4);
			withdraw_cash.AddTransition(&emit_50, &s5);
			withdraw_cash.AddTransition(&emit_other, &s6);
			withdraw_cash.AddTransition(&return_card, &s7);
			StateProcessImpl withdraw_cash_obj;
			withdraw_cash_obj.AddTextLine("Please select the amount");
			withdraw_cash_obj.AddInputOption('1', &s3, "\x9C 10 ");
			withdraw_cash_obj.AddInputOption('2', &s4, "\x9C 20");
			withdraw_cash_obj.AddInputOption('3', &s5, "\x9C 50 ");
			withdraw_cash_obj.AddInputOption('4', &s6, "other");
			withdraw_cash_obj.AddInputOption('5', &s7, "return card");
			withdraw_cash.SetStateProcessObject((StateProcessObject*)&withdraw_cash_obj);
			withdraw_cash.AddTimeout(5000, &more_time_withdraw);

			StateProcessImpl emit_10_obj;
			emit_10_obj.AddTextLine("Machine Emits 10");
			emit_10.SetStateProcessObject((StateProcessObject*)&emit_10_obj);
			emit_10.AddTimeout(4000, &return_card);

			StateProcessImpl emit_20_obj;
			emit_20_obj.AddTextLine("Machine Emits 20");
			emit_20.SetStateProcessObject((StateProcessObject*)&emit_20_obj);
			emit_20.AddTimeout(4000, &return_card);

			StateProcessImpl emit_50_obj;
			emit_50_obj.AddTextLine("Machine Emits 50");
			emit_50.SetStateProcessObject((StateProcessObject*)&emit_50_obj);
			emit_50.AddTimeout(4000, &return_card);

			StateProcessImpl emit_other_obj;
			emit_other_obj.AddTextLine("Machine Emits other");
			emit_other_obj.AddTextLine("todo ... ");
			emit_other.SetStateProcessObject((StateProcessObject*)&emit_other_obj);
			emit_other.AddTimeout(4000, &return_card);
			


		

			StateMachine m;
			m.SetStartState(&select_option);

			char c = 0;



			

			//system("cls");

			while ( m.GetCurrentState() != &return_card)
			{

				/* Use _getch to throw key away. */
				//printf("\nKey struck was '%c'\n", _getch());
				//cout << "Current State: " << total_time << endl;// state_names[m.GetCurrentState()->m_id] << endl;
				m.Process(0.1);

			}
			m.Process(0.1);

		}
	};


#include <thread>
#include <future>
#include <chrono>

	namespace VECTOR_STATE_MACHINE_2
	{
		using namespace TEST_STATES;

		class State;
		class Transition;




		// stack overflow
		//http://stackoverflow.com/questions/32693103/threaded-timer-interrupting-a-sleep-stopping-it
		class ThreadTimer
		{
		public:

			ThreadTimer() {}

			~ThreadTimer()
			{
				Stop();
			}

			void Start(std::chrono::milliseconds const & interval,
				std::function<void(void)> const & callback)
			{
				Stop();

				{
					auto locked = std::unique_lock<std::mutex>(mutex);
					stop = false;
				}

				thread = std::thread([=]()
				{
					auto locked = std::unique_lock<std::mutex>(mutex);

					while (!stop) // We hold the mutex that protects stop
					{
						auto result = terminate.wait_for(locked, interval);

						if (result == std::cv_status::timeout)
						{
							callback();
						}
					}
				});
			}

			void Stop()
			{
				{
					// Set the predicate
					auto locked = std::unique_lock<std::mutex>(mutex);
					stop = true;
				}

				// Tell the thread the predicate has changed
				terminate.notify_one();

				if (thread.joinable())
				{
					thread.join();
				}
			}

		private:

			bool stop; // This is the thing the thread is waiting for
			std::thread thread;
			std::mutex mutex;
			std::condition_variable terminate;
		};



		class Signal
		{
		public:
			Signal(int signal_id)
			{
				id = signal_id;
			}
			int id;
		};

		class Transition
		{
		public:
			Transition(State *From, State *To, int signal)
			{
				from = From;
				to = To;
				signal_id = signal;
			}

			State* Fire_(Signal* signal)
			{
				if (signal_id == signal->id)
				{
					return to;
				}

				return from;
			}

			int signal_id;
			State *from;
			State *to;

		};

		class MessagePrint
		{
		public:
			void PrintMessage()
			{
				for (string str : message_lines)
				{
					cout << str << endl;
				}
			}
			MessagePrint* AddLine(string newline)
			{
				message_lines.push_back(newline);
				return this;
			}
			vector<string> message_lines;
		};




		class InputProcessor
		{
		public:
			std::mutex m_mut;
			void AddBinding(char c, Signal *s)
			{
				m_input_signal_map[c] = s;
				user_inputs.push_back(c);
			}
			void AddBinding(char c, Signal *s, string text)
			{
				m_input_signal_map[c] = s;
				user_inputs.push_back(c);
				m_input_text_map[c] = text;
			}


			

			Signal*  GetInput()
			{
				if (keyHit == 0)
					return 0;
				else
				{
					for (char a : user_inputs)
					{
						if (a == keyHit)
						{
							return  m_input_signal_map[a];

						}
					}
				}
				return 0;
			}

			char keyHit = 0;
			void SetHitKey(char val)
			{
				keyHit = val;
			}

			Signal* Process(bool needPrint)
			{
				//cout << endl;c
				//cout << "Enter an option" << endl;
				if (needPrint)
				{ 
					for (char a : user_inputs)
					{
						if (m_input_text_map.bucket_count() != 0)
							cout << a << ": " << m_input_text_map[a] << endl;
						else
						{
							cout << a << endl;
						}
					}
				}
				Signal* s = 0;

				//future<Signal*> f1 = async( &VECTOR_STATE_MACHINE::InputProcessor::GetInput, this);
				return 0;

				//return (Signal*)f2.get();

			}

			vector< char > user_inputs;
			unordered_map <char, Signal*> m_input_signal_map;
			unordered_map <char, string> m_input_text_map;
		};

		class StateProcessObject
		{
		public:
			virtual Signal* Process(bool needPrint) = 0;
			virtual void SetHitKey(char val) = 0;
			virtual bool HasInput() = 0;
			virtual InputProcessor *GetInputProcessor() = 0;
			
			
		};

		class StateProcessImpl : public StateProcessObject
		{
		public:

			Signal* Process(bool needPrint)
			{
				if (needPrint)
				{ 

					if (m_message)
					{
						m_message->PrintMessage();
					}
				}

				if (inputs)
				{
					Signal *s = inputs->Process(needPrint);
					if (s != 0)
					{
						return s;
					}
				}

				return 0;
			}

			InputProcessor *GetInputProcessor(){
				return inputs;
			}

			bool HasInput(){ return inputs != 0; }

			StateProcessObject* AddTextLine(string line)
			{
				if (!m_message)
					m_message = new MessagePrint();

				m_message->AddLine(line);
				return (StateProcessObject*)this;

			}

			StateProcessObject* AddInputOption(char c, Signal *s)
			{
				if (inputs == 0)
					inputs = new InputProcessor();

				inputs->AddBinding(c, s);
				return (StateProcessObject*)this;
			}
			StateProcessObject* AddInputOption(char c, Signal *s, string text)
			{
				if (inputs == 0)
					inputs = new InputProcessor();

				inputs->AddBinding(c, s, text);
				return (StateProcessObject*)this;
			}

			void SetHitKey(char val)
			{
				if (inputs) inputs->SetHitKey(val);
			}

			StateProcessImpl()
			{

			}
			~StateProcessImpl()
			{
				if (m_message)
					delete m_message;
				if (inputs)
					delete inputs;
			}

			MessagePrint *m_message = 0;
			InputProcessor *inputs = 0;



		};

		class State
		{
		public:
			int m_id = -1;

			State(int id)
			{
				m_id = id;

			}
			~State()
			{

			}

			void SetStateProcessObject(StateProcessObject* obj)
			{
				this->m_stateProcessObject = obj;
			}

			StateProcessObject *GetStateProcessObject()
			{
				return m_stateProcessObject;
			}

			void OnActivate()
			{
				bActivateTimeout = false;
				total_time = 0.0;
				needPrint = true;

			}

			void OnDeactivate()
			{
				total_time = 0.0;
				needPrint = false;
			}

			bool needPrint = true;

			State* Process(double dt)
			{
				total_time += dt;

				Signal *s = 0;

				if (m_stateProcessObject)
				{
					s = m_stateProcessObject->Process(needPrint);

					if (needPrint)
						needPrint = false;
				}

				if (this->bActivateTimeout)
				{
					return Activate(timeout);
				}

				if (s) return Activate(s);

				return this;

			}



			State *Activate(Signal *c)
			{
				State* output = this;
				for (const auto& l : m_tr_list) {
					output = l->Fire_(c);
					if (output != this)
					{
						this->OnDeactivate();
						output->OnActivate();

						return output;
					}
				}

				return this;
			}

			Transition* AddTransition(State* p, Signal *c)
			{
				Transition *pNewTransition = new Transition(this, p, c->id);

				m_tr_list.push_back(pNewTransition);

				return pNewTransition;
			}

			void AddTimeout(double stopTime, State* timeoutState)
			{


				timeout = new Signal(-10000);
				AddTransition(timeoutState, timeout);

				m_stopTime = stopTime;

			}

			void Callback()
			{
				bActivateTimeout = true;



			}

		//	std::unique_ptr<ThreadTimer>  timer;// = 0;

			vector< Transition* > m_tr_list;
			double m_stopTime = 0.0;
			Signal *timeout = 0;

			double total_time;
			bool bActivateTimeout = false;


			StateProcessObject *m_stateProcessObject = 0;

		};





		class StateMachine
		{
		public:
			Timer m_timer;

			double total_time = 0.0;

			double time_delta = 0.0;

			StateMachine()
			{
				m_timer.Start();

			}

			void Process(double dt)
			{
				time_delta = m_timer.Update();
				total_time += time_delta;
				m_next_State = m_current_State->Process(time_delta);
				if (m_next_State != 0 && m_next_State != m_current_State)
				{
					m_timer.Reset();
					m_current_State = m_next_State;
				}
			}


			State* ProcessEvent(Signal *evt)
			{
				//if (m_current_State >= 0 && m_current_State < m_states.size())
				m_current_State = m_current_State->Activate(evt);

				return m_current_State;
			}
			State* GetCurrentState()
			{
				return m_current_State;
			}
			void SetStartState(State* start)
			{
				m_current_State = start;
			}

			State* m_current_State = 0;
			State* m_next_State = 0;
			vector<State*> m_states;
		};



		void RunTest()
		{
			cout << endl;
			cout << "****************************************************" << endl;

			State start_state(START_STATE);
			State middle_state(MIDDLE_STATE);
			State end_state(END_STATE);

			Signal s1(EVENT_1);
			Signal s2(EVENT_2);
			Signal s3(EVENT_3);
			Signal s4(EVENT_4);
			Signal s5(EVENT_5);
			Signal s6(EVENT_6);

			start_state.AddTransition(&middle_state, &s1);
			start_state.AddTransition(&end_state, &s2);

			middle_state.AddTransition(&end_state, &s3);
			middle_state.AddTransition(&start_state, &s4);

			end_state.AddTransition(&middle_state, &s5);
			end_state.AddTransition(&start_state, &s6);

			StateMachine m;
			m.SetStartState(&start_state);

			Signal *state_events[6] = { &s1, &s2, &s3, &s4, &s5, &s6 };


			for (int i = 0; i < 7; i++)
			{
				cout << "State machine current state:   ";
				State* st = m.GetCurrentState();

				switch (STATES(st->m_id))
				{
				case STATES::START_STATE:
					cout << "START_STATE" << endl;
					break;
				case STATES::MIDDLE_STATE:
					cout << "MIDDLE_STATE" << endl;
					break;
				case STATES::END_STATE:
					cout << "END_STATE" << endl;
					break;
				default:
					break;
				};
				cout << "performing transition: " << string_events[transitions[i]] << endl;
				st = m.ProcessEvent(state_events[transitions[i]]);
				//state_machine.stateTransition(transitions[i]);
			}
		}

		char get_input(const std::atomic_bool& cancelled)
		{
			
			char c = 0;
			if (std::cin.get(c) || cancelled)
			{


				return c;
			}
			return c;
		}
		void RunTest3()
		{
			enum TEST_STATES_2 {
				SELECT_OPTION,
				VIEW_BALANCE,
				WITHDRAW_CASH,
				PRINT_STATEMENT,
				MORE_TIME,
				MORE_TIME_WITHDRAW,
				ANOTHER_SERVICE,
				EMIT_10,
				EMIT_20,
				EMIT_50,
				EMIT_OTHER,
				RETURN_CARD
			};

			string state_names[12] = {
				"SELECT_OPTION",
				"VIEW_BALANCE",
				"WITHDRAW_CASH",
				"PRINT_STATEMENT",
				"MORE_TIME",
				"MORE_TIME_WITHDRAW"
				"ANOTHER_SERVICE",
				"EMIT_10",
				"EMIT_20",
				"EMIT_50",
				"EMIT_OTHER",
				"RETURN_CARD"
			};
			Signal s1(1);
			Signal s2(2);
			Signal s3(3);
			Signal s4(4);
			Signal s5(5);
			Signal s6(6);
			Signal s7(7);
			Signal s8(8);
			Signal s9(9);
			Signal s10(10);

			State select_option(SELECT_OPTION);
			State view_balance(VIEW_BALANCE);
			State withdraw_cash(WITHDRAW_CASH);
			State print_statement(PRINT_STATEMENT);
			State more_time(MORE_TIME);
			State more_time_withdraw(MORE_TIME_WITHDRAW);
			State another_service(ANOTHER_SERVICE);
			State emit_10(EMIT_10);
			State emit_20(EMIT_20);
			State emit_50(EMIT_50);
			State emit_other(EMIT_OTHER);
			State return_card(RETURN_CARD);

			select_option.AddTransition(&view_balance, &s1);
			select_option.AddTransition(&withdraw_cash, &s2);
			select_option.AddTransition(&print_statement, &s3);
			StateProcessImpl select_option_obj;
			select_option_obj.AddTextLine("Select an option");
			select_option_obj.AddInputOption('1', &s1, "View Balance");
			select_option_obj.AddInputOption('2', &s2, "Withdraw Cash");
			select_option_obj.AddInputOption('3', &s3, "Print Statement");
			select_option.SetStateProcessObject((StateProcessObject*)&select_option_obj);
			select_option.AddTimeout(5, &more_time);

			more_time.AddTransition(&select_option, &s3);
			more_time.AddTransition(&return_card, &s4);
			StateProcessImpl more_time_obj;
			more_time_obj.AddTextLine("Would you like More Time? ");
			more_time_obj.AddInputOption('1', &s3, "yes");
			more_time_obj.AddInputOption('2', &s4, "no");
			more_time.SetStateProcessObject((StateProcessObject*)&more_time_obj);
			more_time.AddTimeout(5, &return_card);

			more_time_withdraw.AddTransition(&withdraw_cash, &s8);
			more_time_withdraw.AddTransition(&return_card, &s9);
			StateProcessImpl more_time_withdraw_obj;
			more_time_withdraw_obj.AddTextLine("Would you like More Time? ");
			more_time_withdraw_obj.AddInputOption('1', &s8, "yes");
			more_time_withdraw_obj.AddInputOption('2', &s9, "no");
			more_time_withdraw.SetStateProcessObject((StateProcessObject*)&more_time_withdraw_obj);
			more_time_withdraw.AddTimeout(10, &return_card);

			view_balance.AddTransition(&select_option, &s3);
			view_balance.AddTransition(&return_card, &s4);
			StateProcessImpl view_balance_obj;
			view_balance_obj.AddTextLine("Your balance is *database lookup* ");
			view_balance_obj.AddTextLine("Would you like another service? ");
			view_balance_obj.AddInputOption('1', &s3, "yes");
			view_balance_obj.AddInputOption('2', &s4, "no");
			view_balance.SetStateProcessObject((StateProcessObject*)&view_balance_obj);
			view_balance.AddTimeout(5, &return_card);
			//front_left.AddTimeout(5, &enter);

			print_statement.AddTransition(&select_option, &s3);
			print_statement.AddTransition(&return_card, &s4);
			StateProcessImpl print_statement_obj;
			print_statement_obj.AddTextLine("System prints balance statement *database lookup* ");
			print_statement_obj.AddTextLine("Would you like another service? ");
			print_statement_obj.AddInputOption('1', &s3, "yes");
			print_statement_obj.AddInputOption('2', &s4, "no");
			print_statement.SetStateProcessObject((StateProcessObject*)&print_statement_obj);
			print_statement.AddTimeout(5, &return_card);

			//front_right.AddTransition(&center_right, &s5);
			StateProcessImpl return_card_obj;
			return_card_obj.AddTextLine("Please take your card!");
			return_card_obj.AddTextLine("have a great day!");
			return_card.SetStateProcessObject((StateProcessObject*)&return_card_obj);


			withdraw_cash.AddTransition(&emit_10, &s3);
			withdraw_cash.AddTransition(&emit_20, &s4);
			withdraw_cash.AddTransition(&emit_50, &s5);
			withdraw_cash.AddTransition(&emit_other, &s6);
			withdraw_cash.AddTransition(&return_card, &s7);
			StateProcessImpl withdraw_cash_obj;
			withdraw_cash_obj.AddTextLine("Please select the amount");
			withdraw_cash_obj.AddInputOption('1', &s3, "\x9C 10 ");
			withdraw_cash_obj.AddInputOption('2', &s4, "\x9C 20");
			withdraw_cash_obj.AddInputOption('3', &s5, "\x9C 50 ");
			withdraw_cash_obj.AddInputOption('4', &s6, "other");
			withdraw_cash_obj.AddInputOption('5', &s7, "return card");
			withdraw_cash.SetStateProcessObject((StateProcessObject*)&withdraw_cash_obj);
			withdraw_cash.AddTimeout(5, &more_time_withdraw);

			StateProcessImpl emit_10_obj;
			emit_10_obj.AddTextLine("Machine Emits 10");
			emit_10.SetStateProcessObject((StateProcessObject*)&emit_10_obj);
			emit_10.AddTimeout(4, &return_card);

			StateProcessImpl emit_20_obj;
			emit_20_obj.AddTextLine("Machine Emits 20");
			emit_20.SetStateProcessObject((StateProcessObject*)&emit_20_obj);
			emit_20.AddTimeout(4, &return_card);

			StateProcessImpl emit_50_obj;
			emit_50_obj.AddTextLine("Machine Emits 50");
			emit_50.SetStateProcessObject((StateProcessObject*)&emit_50_obj);
			emit_50.AddTimeout(4, &return_card);

			StateProcessImpl emit_other_obj;
			emit_other_obj.AddTextLine("Machine Emits other");
			emit_other_obj.AddTextLine("todo ... ");
			emit_other.SetStateProcessObject((StateProcessObject*)&emit_other_obj);
			emit_other.AddTimeout(4, &return_card);





			StateMachine m;
			m.SetStartState(&select_option);







			//system("cls");
			bool needPrint = true;
			while (m.GetCurrentState() != &return_card)
			{

				//m.Process(0.1);
				
				// what a mess ... 
				State* s = m.GetCurrentState();
				s->GetStateProcessObject()->Process(needPrint);
				needPrint = false;
				if ( s->m_stopTime != 0.0 && s->GetStateProcessObject()->HasInput() )  
				{
					std::atomic_bool cancellation_token;
					// Execute lambda asyncronously.
					auto f = std::async(std::launch::async, get_input, std::ref(cancellation_token)

					);

					std::chrono::seconds sec((int)s->m_stopTime);
					std::chrono::seconds ten_sec(10);

					//	std::chrono::time_point <std::chrono::system_clock, std::chrono::duration<int>> tp_seconds(std::chrono::duration<int>(1));
					std::chrono::system_clock::time_point eight_seconds_passed
						= std::chrono::system_clock::now() + std::chrono::seconds((int)s->m_stopTime);


					std::future_status status_for = f.wait_for(sec);
					//std::future_status status_until = f.wait_until(eight_seconds_passed);

					// Continue execution in main thread.
					
					// what a mess ... 
					if (status_for == std::future_status::ready)
					{
						s->bActivateTimeout = false;
						char XX = f.get();
						s->GetStateProcessObject()->SetHitKey(XX);
						if (s->GetStateProcessObject()->HasInput())
						{
							InputProcessor * ip = s->GetStateProcessObject()->GetInputProcessor();
							bool foundInput = false;
							for (char a : ip->user_inputs)
							{
								if (a == XX)
								{
									m.m_current_State = m.m_current_State->Activate(ip->m_input_signal_map[a]);
									m.m_next_State = m.m_current_State;
									foundInput = true;
									needPrint = true;
									std::cin.clear();
									std::cin.ignore(INT_MAX, '\n');
									break;
								}
							}

							/*if (foundInput == false)
							{
								s->OnActivate();
							}*/
						}
						else
						{
							s->GetStateProcessObject()->SetHitKey(0);
							m.m_current_State = s->Activate(s->timeout);
							needPrint = true;
							/*istringstream iss("\0");
							streambuf *backup;
							backup = cin.rdbuf();
							cin.rdbuf(iss.rdbuf());
							cin.rdbuf(backup);*/
							cin.clear();
							
						}
						//std::cout << "still waiting..." << std::endl;
						//cancellation_token = true;

					}
					else if (status_for == std::future_status::timeout || status_for == std::future_status::deferred)
					{
						//s->bActivateTimeout = true;
						s->GetStateProcessObject()->SetHitKey(0);
						m.m_current_State = s->Activate(s->timeout);
						needPrint = true;
						cancellation_token = true;
						//char XX = f.get();
						
					}
					else
					{
						needPrint = true;
					}
					
					
				//	std::cout << "Input was: " << f.get() << std::endl;
				}
				else
				{
					//	std::chrono::time_point <std::chrono::system_clock, std::chrono::duration<int>> tp_seconds(std::chrono::duration<int>(1));
					std::chrono::system_clock::time_point eight_seconds_passed
						= std::chrono::system_clock::now() + std::chrono::seconds((int)s->m_stopTime);


					

					auto f = std::async(std::launch::async, [] {
						cout << "done" << endl;
					});

					//std::future_status status_for = f.wait_for(sec);
					std::future_status status_until = f.wait_until(eight_seconds_passed);

					if (status_until == std::future_status::ready)
					{
						s->GetStateProcessObject()->SetHitKey(0);
						m.m_current_State = s->Activate(s->timeout);
					}
					else
					{
						s->GetStateProcessObject()->SetHitKey(0);
						m.m_current_State = s->Activate(s->timeout);
					}
					needPrint = true;
				}
			//	m.Process(0.1);

			}
			
			m.Process(0.1);

		}
	};
};




/*
string reverse_string(const string& s)
{
	cout << "Reversing " << s << endl;
	string ss(s);
	reverse(ss.begin(), ss.end());
	return ss;
}*/


#include <thread>
#include <future>



int main(int argc, char** argv)
{
//	EXPERT_VERSION_1::RunExample();


	cout << "=============================================================================" << endl;
	cout << "Processing Version Cash Machine version 2: This version uses C++ 11 async calls" << endl;
	cout << "NOTE: IF YOU RUN OUT OF TIME YOU NEED TO INPUT THE ANSWER TWICE AND HIT ENTER EACH TIME " << endl;
	cout << "=============================================================================" << endl << endl;
	STATE_MACHINE::VECTOR_STATE_MACHINE_2::RunTest3();
	system("cls");

//	STATE_MACHINE::LINKED_STATE_MACHINE::RunTest();
	cout << "=============================================================================" << endl;
	cout << "Processing Version Cash Machine version 3: This version uses a threaded timer." << endl;
	cout << "And is currently only implemented for Windows " << endl;
	cout << "=============================================================================" << endl << endl;
	
	
		std::this_thread::sleep_for(std::chrono::seconds(2));

		

	
	STATE_MACHINE::VECTOR_STATE_MACHINE::RunTest3();
	
	//cin.ignore(INT_MAX);


	/*
	future<string> f = async(reverse_string, "Roma tibi subito motibus ibit amor");
	auto g = async(reverse_string, "Anita lava la tina");
	auto h = async(reverse_string, "A man, a plan, a canal: Panama");

	cout << "SHOWING RESULTS...." << endl;

	cout << "R1: " << f.get() << endl << endl;
	cout << "R2: " << g.get() << endl << endl;
	cout << "R3: " << h.get() << endl << endl;
	*/

	// Enable standard literals as 2s and ""s.
	


	return 0;
}

