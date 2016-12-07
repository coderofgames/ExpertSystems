// Bayes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "matrix_solver.h"
#include "Timer.h"

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

	namespace LINKED_STATE_MACHINE_VERSION_2
	{
		using namespace TEST_STATES;

		class BaseState;
		class State;
		template< class SIGNAL> class Transition;

		enum SIGNAL_TYPE {BASE, FLOAT, LIST};

		class Signal
		{
		public:
			Signal(int signal_id)
			{
				id = signal_id;
			}
			int id;
			int m_type = SIGNAL_TYPE::BASE;
		};

		class Float_Signal : public Signal
		{
		public:
			Float_Signal(int signal_id, float value) : Signal(signal_id)
			{
				m_val = value;
				m_type = SIGNAL_TYPE::FLOAT;
			}
			float m_val;
		};

		enum LOGICAL_OP { AND, OR, XOR, NAND };

		class LinkedSignal : public Float_Signal
		{
		public:
			LinkedSignal(int signal_id, float value) : Float_Signal(signal_id, value)
			{
				m_type = SIGNAL_TYPE::LIST;
			}
			void AddSignal(LinkedSignal* s)
			{
				if (p_next == this)
				{
					p_next = s;
					s->p_prev = this;
					this->p_prev = s;
					s->p_next = this;
				}
				else
				{
					p_prev->p_next = s;
					s->p_prev = p_prev;
					p_prev = s;
					s->p_next = this;
				}
			}

			bool Evaluate(LOGICAL_OP op)
			{
				switch (op)
				{
				case AND:
				{
					LinkedSignal *temp = this;
					if (temp == p_next)
					{
						return temp->m_val == 1.0;
					}
					else
					{
						if (temp->m_val == 0.0) return false;
						temp = temp->p_next;
						while (temp)
						{
							if (temp == this) { break; }
							if (temp->m_val != 1.0f)
							{
								return false;
							}
							temp = temp->p_next;
						}
						return true;
					}
					break;
				}
				case OR:
				{
					LinkedSignal *temp = this;
					if (temp == p_next)
					{
						return temp->m_val == 1.0;
					}
					else
					{
						if (temp->m_val == 1.0) return true;
						temp = temp->p_next;
						while (temp)
						{
							if (temp == this) { break; }
							if (temp->m_val == 1.0f)
							{
								return true;
							}
							temp = temp->p_next;
						}
						return false;
					}
					break;
				}
				case XOR:
					return true;
				case NAND:
					return true;
				}
			}
			LinkedSignal *p_next = this;
			LinkedSignal *p_prev = this;
		};

		

		
		template<class SIGNAL>
		class Transition
		{
		public:
			Transition(BaseState *From, BaseState *To, SIGNAL* signal)
			{
				from = From;
				to = To;
				next = this;
				prev = this;
				m_signal = signal;
			}

			virtual BaseState* Fire_(SIGNAL* signal) = 0;
		
			SIGNAL* m_signal = 0;
			BaseState *from;
			BaseState *to;
			Transition *next = 0;
			Transition *prev = 0;
		};

		class StateTransition : public Transition <Signal>
		{
		public:
			StateTransition(BaseState *From, BaseState *To, Signal* signal) : Transition(From, To, signal)
			{
			}
			BaseState* Fire_(Signal* signal)
			{
				if (signal->id == m_signal->id)
				{
					return to;
				}
				return from;
			}
		};

		
		
		class LogicalTransition : public Transition<LinkedSignal>
		{
		public:
			LogicalTransition(BaseState *From, BaseState *To, LinkedSignal* signal, LOGICAL_OP t_op) : Transition(From, To, signal)
			{
				op = t_op;
			}
			BaseState* Fire_(LinkedSignal* signal)
			{
				if (signal->id == m_signal->id)
				{
					bool result = signal->Evaluate(op);
					if (result)
						return to;
				}
				return from;
			}
			LOGICAL_OP op = LOGICAL_OP::OR;

		};
		
		class BaseState
		{
		public:
			int m_id = -1;
			BaseState(int id) { m_id = id; }
			virtual BaseState *Activate(Signal *c) = 0;
			virtual void AddTransition(State* p, Signal *c) = 0;
		};

		class State : public BaseState
		{
		public:
			State(int id) : BaseState(id)
			{
				
			}
			BaseState *Activate(Signal *c)
			{
				BaseState* output = this;
				StateTransition* temp = m_start;
				while (temp)
				{
					output = temp->Fire_(c);
					if (output != this)
						return output;
					temp = (StateTransition*)temp->next;
					if (temp == m_start)
						break;
				}
				return output;
			}

			void AddTransition(State* p, Signal *c)
			{
				StateTransition *pNewTransition = new StateTransition(this, p, c);

				if (m_start)
				{
					StateTransition *temp = m_start;
					StateTransition *prev = (StateTransition*) m_start->prev;

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


			}


			StateTransition *m_start = 0;
		};

		class LState : public BaseState
		{
		public:
			LState(int id) : BaseState(id)
			{

			}
			BaseState *Activate(Signal *c)
			{
				BaseState* output = (State*)this;
				LogicalTransition* temp = m_start;
				while (temp)
				{
					output = temp->Fire_((LinkedSignal*)c);
					if (output != (State*)this)
						return output;
					temp = (LogicalTransition*)temp->next;
					if (temp == m_start)
						break;
				}
				return output;
			}

			void AddTransition(State* p, Signal *c)
			{
				LogicalTransition *pNewTransition = new LogicalTransition(this, p, (LinkedSignal*)c, OR);

				if (m_start)
				{
					LogicalTransition *temp = m_start;
					LogicalTransition *prev = (LogicalTransition*)m_start->prev;

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


			}


			LogicalTransition *m_start = 0;

		};


		class StateMachine
		{
		public:

			BaseState* ProcessEvent(Signal *evt)
			{
				//if (m_current_State >= 0 && m_current_State < m_states.size())
				m_current_State = m_current_State->Activate(evt);

				return m_current_State;
			}
			BaseState* GetCurrentState()
			{
				return m_current_State;
			}
			void SetStartState(BaseState* start)
			{
				m_current_State = start;
			}

			BaseState* m_current_State = 0;
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
				BaseState* st = m.GetCurrentState();

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

	namespace LINKED_STATE_MACHINE_PROCESSOR
	{
		using namespace LINKED_STATE_MACHINE;
		enum CASH_MACHINE_STATES {
			OPTIONS, VIEW_BALANCE, QUERY_MORE_TIME, QUERY_OTHER_TRANSACTION,
			SELECT_QUANTITY, DISPENSE_MESSAGE, TAKE_CARD, MORE_TIME
		};
		string cash_machine_state_strings[8] = { "OPTIONS", "VIEW_BALANCE", "QUERY_MORE_TIME", "QUERY_OTHER_TRANSACTION",
			"SELECT_QUANTITY", "DISPENSE_MESSAGE", "TAKE_CARD", "MORE_TIME" };
		class StateImpl : public State
		{
		public:
			StateImpl(int id) : State(id)
			{

			}

			virtual State* Process()
			{
				cout << "Processing State: " << cash_machine_state_strings[this->m_id] << endl;
				return this;
			}



		};

		class TimedState : public StateImpl
		{
		public:

			TimedState(int id) : StateImpl(id)
			{

			}

			void SetTimeout(double TimeOut, Signal* stateTimeOut)
			{
				this->time_out = TimeOut;
				this->time_out_signal = stateTimeOut;
			}
			
			State* Tick(double dt)
			{
				elapsed_time += dt;
				if (elapsed_time >= time_out)
				{
					if (this->time_out_signal)
					{
						cout << "	state: " << cash_machine_state_strings[this->m_id] << " timed out" << endl;
						return	this->Activate(this->time_out_signal);
					}
				}
				
				return this;
			}
			
			Signal *time_out_signal = 0;

			double start_time = 0.0;
			double elapsed_time = 0.0;
			double time_out = 0.0;
		};


		
		class MessageState : public TimedState
		{
		public:
			MessageState(int id) : TimedState(id)
			{

			}

			void SetMessage(string Message){
				message = Message;
			}

			virtual State* Process()
			{
				cout << message << "      " << endl;
				return StateImpl::Process();
				
			}

			string message = "";
		};

		class InputState : public MessageState
		{
		public:
			InputState(int id) : MessageState(id)
			{

			}

			virtual State* Process()
			{
				cout << "select an option" << endl;
				for (int i = 0; i < options.size(); i++)
					cout << "option: " << i << " " << options[i] << endl;


				char ch = -1;
				cin >> ch;
				
				if (ch >= '1' && ch <= '1'+ options.size())
				{
					int var = (int)ch - (int)'1';

					int the_signal = options[var];

					State* output = this;
					Transition* temp = m_start;
					while (temp)
					{
						output = temp->Fire_(the_signal);
						if (output != this)
							return output;
						temp = temp->next;
						if (temp == m_start)
							break;
					}
					return output;
				}
				else
				{
					cout << "Select a valid otion " << endl;
				}
				
				return MessageState::Process();

			}

			void AddOption(int newOption)
			{
				options.push_back(newOption);

			}

			vector<int> options;
		};

		class BalanceState : public TimedState
		{
		public:
			BalanceState() : TimedState(VIEW_BALANCE)
			{}
			State* Process()
			{
				return TimedState::Process();
			}
		};


		void RunTestCashMachine()
		{
			cout << endl;
			cout << "****************************************************" << endl;

			enum CASH_MACHINE_EVENTS {OPTION_SELECT_1, OPTION_SELECT_2, OPTION_SELECT_3 };
			Signal s1(OPTION_SELECT_1);
			Signal s2(OPTION_SELECT_2);
			Signal s3(OPTION_SELECT_3);
	

			InputState start_state(OPTIONS);
			start_state.AddOption(OPTION_SELECT_1); 
			start_state.AddOption(OPTION_SELECT_2);
			start_state.AddOption(OPTION_SELECT_3);
			start_state.SetTimeout(10, &s3);

			MessageState view_balance_state(VIEW_BALANCE);
			view_balance_state.SetMessage("Your Balance Is 100000 kudos");
			view_balance_state.SetTimeout(10, &s1);

			InputState time_query_state(QUERY_MORE_TIME);
			time_query_state.AddOption(OPTION_SELECT_1);
			time_query_state.AddOption(OPTION_SELECT_2);
			time_query_state.SetTimeout(10, &s3);

			InputState other_transaction_query_state(QUERY_OTHER_TRANSACTION);
			other_transaction_query_state.AddOption(OPTION_SELECT_1);
			other_transaction_query_state.AddOption(OPTION_SELECT_2);
			other_transaction_query_state.SetTimeout(10, &s3);

			InputState select_quantity_state(SELECT_QUANTITY);
			select_quantity_state.AddOption(OPTION_SELECT_1);
			select_quantity_state.AddOption(OPTION_SELECT_2);
			select_quantity_state.SetTimeout(10, &s2);

			MessageState dispense_state(DISPENSE_MESSAGE);
			dispense_state.SetMessage("dispensing your money");
			view_balance_state.SetTimeout(2, &s1);
			

			InputState time_query2_state(MORE_TIME);
			time_query2_state.AddOption(OPTION_SELECT_1);
			time_query2_state.AddOption(OPTION_SELECT_2);
			time_query2_state.SetTimeout(10, &s3);

			MessageState take_card_state(TAKE_CARD);
			dispense_state.SetMessage("please take your card");


			start_state.AddTransition(&view_balance_state, &s1);
			start_state.AddTransition(&select_quantity_state, &s2);
			start_state.AddTransition(&take_card_state, &s3);

			//time_query_state.AddTransition(&start_state, &s1);

			view_balance_state.AddTransition(&other_transaction_query_state, &s1);

			other_transaction_query_state.AddTransition(&start_state, &s1);
			other_transaction_query_state.AddTransition(&take_card_state, &s2);

			select_quantity_state.AddTransition(&dispense_state, &s1);

		//	end_state.AddTransition(&middle_state, &s5);
		//	end_state.AddTransition(&start_state, &s6);

			StateMachine m;
			m.SetStartState(&start_state);

			Signal *state_events[3] = { &s1, &s2, &s3 };

			char ch = 0;

			Timer t;
			t.Start();
			double start_time = 0.0f;

			while (ch != 'q')
			{
				//t.Update();
				t.Stop();
				double dt = t.GetTimeInSeconds();
				cin >> ch;

				TimedState* st = (TimedState*)m.GetCurrentState();
				m.m_current_State = st->Tick(dt);

				st->Process();


				int i = (int)ch - (int)'1';

				t.Reset();
				t.Start();
			}
			

		}

		void RunTest()
		{
			cout << endl;
			cout << "****************************************************" << endl;

			StateImpl start_state(START_STATE);
			StateImpl middle_state(MIDDLE_STATE);
			StateImpl end_state(END_STATE);

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

			char ch =0;

			while (ch != 'q')
			{
				cin >> ch;

				StateImpl* st = (StateImpl*)m.GetCurrentState();
				st->Process();
				
				if (ch >= '1' && ch <= '6')
				{
					int i = (int)ch - (int)'1';
					cout << "performing transition: " << string_events[i] << endl;
					m.ProcessEvent(state_events[i]);
				}

			}
		
		}


	};

	namespace VECTOR_STATE_MACHINE
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
			void AddBinding(char c, Signal *s)
			{
				m_input_signal_map[c] = s;
				user_inputs.push_back(c);
			}

			Signal* Process()
			{

				cout << endl;
				cout << "Enter an option" << endl;
				for (char a : user_inputs)
				{
					cout << a << endl;
				}

				char c = 0;
				cin >> c;
				for (char a : user_inputs)
				{
					if (a == c)
					{
						return m_input_signal_map[c];
					}
				}
				
				return 0;
			}

			vector< char > user_inputs;
			unordered_map <char, Signal*> m_input_signal_map;
		};

		class StateProcessObject
		{
		public:
			Signal* Process(bool needPrint){

				if (!needPrint)
					return 0;

					
				if (m_message)	
				{

					m_message->PrintMessage();
				}

				if (inputs)
				{
					Signal *s = inputs->Process();
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
				return this;

			}

			StateProcessObject* AddInputOption(char c, Signal *s)
			{
				if ( inputs == 0 )
					inputs = new InputProcessor();

				inputs->AddBinding(c, s);
				return this;
			}

			StateProcessObject()
			{

			}
			~StateProcessObject()
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
				m_stateProcessObject = new StateProcessObject;
			}
			~State()
			{
				delete m_stateProcessObject;
			}
			void OnActivate()
			{
			//	m_timer.Reset();
			//	m_timer.Start();
				total_time = 0.0;
				needPrint = true;
			}

			void OnDeactivate()
			{
			//	m_timer.Update();
				total_time = 0.0;
				needPrint = false; 
			//	m_timer.Stop();
			//	m_timer.Reset();
			}

			bool needPrint = true;

			State* Process(double dt)
			{
				total_time += dt;

				

				Signal *s = m_stateProcessObject->Process(needPrint);

				if (needPrint)needPrint = false;
				

				if (timeout)
				{
					//m_timer.Update();
					
					
					//double time_taken = m_timer.GetTimeDelta();
					//cout << time_taken << endl;
					if (total_time > m_stopTime)
					{
						return Activate(timeout);
					}
				}

				if (s) return Activate(s);

				return this;

			}

			StateProcessObject* AddMessageLine(string line)
			{
				m_stateProcessObject->AddTextLine(line);
				return m_stateProcessObject;
			}
			void AddInputOption(char c, Signal* s)
			{
				m_stateProcessObject->AddInputOption(c, s);
			}

			State *Activate(Signal *c)
			{
				State* output = this;
				for (const auto& l : m_tr_list) {
					output = l->Fire_(c);
					if (output != this)
					{
						output->OnActivate();
						this->OnDeactivate();
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

			vector< Transition* > m_tr_list;
			double m_stopTime = 0.0;
			Signal *timeout = 0;
			
			double total_time;
			

			StateProcessObject *m_stateProcessObject;

		};





		class StateMachine
		{
		public:

			void Process(double dt)
			{
				m_next_State = m_current_State->Process(dt);
				if (m_next_State!= 0 && m_next_State != m_current_State)
					m_current_State = m_next_State;
				
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

		void RunTest2()
		{
			enum TEST_STATES_2 { ENTER, FRONT_LEFT, FRONT_RIGHT, CENTER_MIDDLE, CENTER_LEFT, CENTER_RIGHT, END};
			string state_names[7] = { "ENTER", "FRONT_LEFT", "FRONT_RIGHT", "CENTER_MIDDLE", "CENTER_LEFT", "CENTER_RIGHT", "END" };
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

			State enter(ENTER);
			State front_left(FRONT_LEFT);
			State front_right(FRONT_RIGHT);
			State center_middle(CENTER_MIDDLE);
			State center_left(CENTER_LEFT);
			State center_right(CENTER_RIGHT);
			State end(END);

			enter.AddTransition(&front_left, &s1);
			enter.AddTransition(&front_right, &s2);
			enter.AddMessageLine("This is the entrance");
			enter.AddMessageLine("Select A Path, LEFT or RIGHT");
			enter.AddInputOption('1', &s1);
			enter.AddInputOption('2', &s2);

			front_left.AddTransition(&center_middle, &s3);
			front_left.AddTransition(&center_left, &s4);
			front_left.AddMessageLine("This is the front left");
			front_left.AddMessageLine("Select a Path, CENTER_MIDDLE or CENTER_LEFT");
			front_left.AddInputOption('1', &s3);
			front_left.AddInputOption('2', &s4);
			front_left.AddTimeout(5, &enter);

			//front_right.AddTransition(&center_right, &s5);
			front_right.AddMessageLine("Heading to next state after 10 seconds");
			front_right.AddTimeout(10, &center_right);

			
			center_left.AddMessageLine("This is a dead end.");
			center_left.AddMessageLine("Heading to front_left after 10 seconds");
			center_left.AddTimeout(10, &front_left);

			
			center_middle.AddTransition(&end, &s6);
			center_middle.AddMessageLine("This is center middle");
			center_middle.AddMessageLine("Heading to front_left after 10 seconds");
			center_middle.AddMessageLine("Select a Path, end or wait");
			center_middle.AddInputOption('1', &s6);
			center_middle.AddInputOption('2', &s1);
			center_middle.AddTimeout(10, &front_left);

			center_right.AddMessageLine("You found the gold.");
			center_right.AddMessageLine("Heading to end after 10 seconds");
			center_right.AddTimeout(10, &end);

			end.AddTimeout(4, &enter);
			end.AddMessageLine("This is the end, heading back to start");

			StateMachine m;
			m.SetStartState(&enter);

			char c = 0;

			Timer m_timer;

			double total_time = 0.0;

			double time_delta = 0.0;
			m_timer.Start();
			time_delta = m_timer.Update();

			total_time += time_delta;

			while (m.GetCurrentState()!= &end)
			{
				time_delta = m_timer.Update();
				total_time += time_delta;
				//cout << "Current State: " << total_time << endl;// state_names[m.GetCurrentState()->m_id] << endl;
				m.Process(time_delta);
			}
			
			
		}

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

	}
};




int main(int argc, char** argv)
{
	EXPERT_VERSION_1::RunExample();



	STATE_MACHINE::LINKED_STATE_MACHINE::RunTest();

	STATE_MACHINE::LINKED_STATE_MACHINE_VERSION_2::RunTest();

//	STATE_MACHINE::LINKED_STATE_MACHINE_PROCESSOR::RunTestCashMachine();

	STATE_MACHINE::VECTOR_STATE_MACHINE::RunTest2();
	return 0;
}

