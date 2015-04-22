
/* 
 *
 * $$ dollar dollar values below to add to cjpp.y  
 *
 */

      Block: LCURLY StatementList RCURLY	{ $$ = $2; }
	| LCURLY RCURLY		{ $$ = new NBlock(); }
	;