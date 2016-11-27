// Bayes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "matrix_solver.h"

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
};




int main(int argc, char** argv)
{
	EXPERT_VERSION_1::RunExample();



	STATE_MACHINE::LINKED_STATE_MACHINE::RunTest();

	STATE_MACHINE::LINKED_STATE_MACHINE_VERSION_2::RunTest();
	return 0;
}

