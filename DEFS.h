#ifndef DEFS_H
#define DEFS_H

//This file contains some global constants and definitions to be used in the project.

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

// TODO: Add any action type here
enum ActionType // The actions supported
{
	ADD_START, //Add start statement
	ADD_END,   //Add end statement
	ADD_DECLARE_VARIABLE, // Add  declare variable statement
	ADD_VALUE_ASSIGN, //Add value assignment statement
	ADD_VAR_ASSIGN,	  //Add variable assignment statement
	ADD_OPER_ASSIGN,  //Add operator assignment statement
	ADD_CONDITION,    //Add a conditional statement (for if and while-loop statements)
	ADD_READ,  //Add read statement
	ADD_WRITE, //Addd write statemetn

	ADD_CONNECTOR, //Add a connector between two statements

	SELECT,		//Select a statement, a connector
	EDIT_STAT,	//Edit a statement

	DEL,   //Delete a figure
	COPY,  //Copy a figure
	CUT,   //Cut a figure
	PASTE, //Paste a figure

	UNDO,		//Undo the last action
	REDO,		//Redo the last action

	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file

	SWITCH_DSN_MODE,	//Switch to Design mode
	SWITCH_SIM_MODE,	//Switch to simulatiom mode

	EXIT,		//Exit the application


	//TODO: ADD THE ACTIONS OF SIMULATION MODE


	DRAWING_AREA,  //A click on the drawing area
	OUTPUT_AREA,   //A click on the output area
	DSN_TOOL,	   //A click on an empty place in the design tool bar
	STATUS, 		   //A click on the status bar


	VALIDATE, //Validate the flowchart
	RUN,     //Run the flowchart
	DEBUG, //Debug the flowchart
	GENERATE, //Generate the flowchart code
	SIM_TOOL  //A click on an empty place in the simulation tool bar

};

// TODO: you should add more items
enum DesignMenuItem // The items of the design menu --> THE ORDER MATTERS
{
	// Corresponding to ActionType order:

	ITM_START,             // ADD_START
	ITM_END,               // ADD_END

	ITM_DECLARE,           // ADD_DECLARE_VARIABLE
	ITM_VALUE_ASSIGN,      // ADD_VALUE_ASSIGN
	ITM_VARIABLE_ASSIGN,   // ADD_VAR_ASSIGN
	ITM_OPERATOR_ASSIGN,   // ADD_OPER_ASSIGN

	ITM_COND,              // ADD_CONDITION
	ITM_INPUT,             // ADD_READ
	ITM_OUTPUT,            // ADD_WRITE

	ITM_CONNECTOR,         // ADD_CONNECTOR

	ITM_SELECT,            // SELECT
	ITM_EDIT,              // EDIT_STAT

	ITM_DELETE,            // DEL
	ITM_COPY,              // COPY
	ITM_CUT,               // CUT
	ITM_PASTE,             // PASTE

	ITM_UNDO,              // UNDO
	ITM_REDO,              // REDO

	ITM_SAVE,              // SAVE
	ITM_LOAD,              // LOAD

	ITM_SWITCH_TO_SIM,     // SWITCH_SIM_MODE
	ITM_EXIT,              // EXIT

	DSN_ITM_CNT            // no. of design menu items (must remain last)
};

// TODO: you should add more items if needed
enum SimMenuItem //The items of the simulation menu
{
	//Note: Items are ordered here as they appear in menu
	ITM_VALIDATE,	//Validate
	ITM_RUN,	    //Run
	ITM_DEBUG,    //Debug
	ITM_GENERATE, //Generate Code
	ITM_UNDO_SIM,     //Undo
	ITM_REDO_SIM,     //Redo
	ITM_SAVE_SIM,     //Save a file
	ITM_LOAD_SIM,     //Load a file
	ITM_SWITCH_TO_DES, //Switch to Design mode
	ITM_EXIT_SIM,
		
	//TODO:Add more items names here
	
	SIM_ITM_CNT		//no. of simulation menu items ==> This should be the last line in this enum
	
};




#ifndef NULL
#define NULL 0
#endif

#endif