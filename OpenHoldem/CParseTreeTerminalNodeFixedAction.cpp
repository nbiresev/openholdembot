//*******************************************************************************
//
// This file is part of the OpenHoldem project
//   Download page:         http://code.google.com/p/openholdembot/
//   Forums:                http://www.maxinmontreal.com/forums/index.php
//   Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//*******************************************************************************
//
// Purpose:
//
//*******************************************************************************

#include "stdafx.h" 
#include "CParseTreeTerminalNodeFixedAction.h"

#include <math.h>
#include "CAutoplayerTrace.h"
#include "CEngineContainer.h"
#include "CFunctionCollection.h"
#include "CParserSymbolTable.h"
#include "CPreferences.h"
#include "CSymbolEngineChipAmounts.h"
#include "CSymbolEngineMemorySymbols.h"
#include "CSymbolEngineOpenPPLUserVariables.h"
#include "CSymbolEngineTableLimits.h"
#include "FloatingPoint_Comparisions.h"
#include "NumericalFunctions.h"
#include "OH_MessageBox.h"
#include "StringFunctions.h"
#include "TokenizerConstants.h"

CParseTreeTerminalNodeFixedAction::CParseTreeTerminalNodeFixedAction(
  int relative_line_number, CString name) : 
  CParseTreeTerminalNodeIdentifier(relative_line_number, 
    name) {
}

CParseTreeTerminalNodeFixedAction::~CParseTreeTerminalNodeFixedAction() {
}

double CParseTreeTerminalNodeFixedAction::Evaluate(bool log /* = false */){
  write_log(preferences.debug_formula(), 
    "[CParseTreeTerminalNode] Evaluating node type %i %s\n", 
		_node_type, TokenString(_node_type));
  p_autoplayer_trace->SetLastEvaluatedRelativeLineNumber(_relative_line_number);
	if (TokenIsElementaryAction(_node_type)) { //?????
		return (0 - _node_type);
  }
	// This must not happen for a terminal node
	assert(false);
	return kUndefined;
}

CString CParseTreeTerminalNodeFixedAction::EvaluateToString(bool log /* = false */) {
  double numerical_result = Evaluate(log);
  CString result;
  if (IsInteger(numerical_result) && EvaluatesToBinaryNumber()) {
    // Generqate binary representation;
    result.Format("%s", IntToBinaryString(int(numerical_result)));
  } else {
    // Generate floating-point representation
    // with 3 digits precision
    result.Format("%.3f", numerical_result);
  }
  return result;
}

CString CParseTreeTerminalNodeFixedAction::Serialize() {
  if (_node_type == kTokenIdentifier) {
    return _terminal_name;
  } else {
    // Unhandled note-type, probably new and therefore not yet handled
    write_log(k_always_log_errors, "[CParseTreeTerminalNode] ERROR: Unhandled node-tzpe %i in serialiyation of parse-tree\n",
      _node_type);
    return "";
  }
}
