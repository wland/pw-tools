#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Collections;
using namespace System::Windows::Forms;

/*
operation
{
}
*/
ref struct Procedure
{
	int type;
	array<Object^>^ parameters;
	int target_type;
	array<Object^>^ target_parameters;
};

/*
condition
{
}
*/
ref struct Condition
{
	int operator_id;
	int argument_bytes;
	array<unsigned char>^  value;

	int condition_type;
	Condition^ condition_left;
	int subnode_2;
	Condition^ condition_right;
	int subnode_3;
};

/*
ai_trigger
{
	int _id;
	struct condition *_cond;
	struct operation *_ops;
	bool _enable;
	bool _default_enable;
	bool _battle_trigger;
}
*/
ref struct ActionSet
{
	int version;
	int id;
	array<unsigned char>^ flags; // 3 Bytes
	array<unsigned char>^ name; // 128 Bytes
	property String^ Name
	{
		String^ get()
		{
			Encoding^ enc = Encoding::GetEncoding("GBK");
			return enc->GetString(name);//->Replace("\0", "");
		}
		void set(String^ value)
		{
			Encoding^ enc = Encoding::GetEncoding("GBK");
			array<unsigned char>^ target = gcnew array<unsigned char>(128);
			array<unsigned char>^ source = enc->GetBytes(value);
			if(target->Length > source->Length)
			{
				Array::Copy(source, target, source->Length);
			}
			else
			{
				Array::Copy(source, target, target->Length);
			}
			name = target;
		}
	}
	Condition^ conditions;
	int procedures_count;
	array<Procedure^>^ procedures;
};

/*
ai_task
{
}
*/
ref struct ActionController
{
	int signature;
	int id;
	int action_sets_count;
	array<ActionSet^>^ action_sets;
};

/*
ai_policy
{
}
*/
ref struct AIPolicy
{
	int signature;
	int action_controllers_count;
	array<ActionController^>^ action_controllers;
};