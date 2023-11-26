public class sym {

    public final static int EOF = 0;
    public final static int MAIN = 1;
    public final static int OPEN_CURLY_BRACKET = 2;
    public final static int CLOSED_CURLY_BRACKET = 3;
    public final static int OPEN_BRACKET = 4;
    public final static int CLOSED_BRACKET = 5;
    public final static int INT = 6;
    public final static int REAL = 7;
    public final static int BOOLEAN = 8;
    public final static int ELSE = 9;
    public final static int IF = 10;
    public final static int ELIF = 11;
    public final static int ID = 12;
    public final static int CONST = 13;
    public final static int ASSIGNMENT = 14;
    public final static int LESS = 15;
    public final static int LESSOREQUAL = 16;
    public final static int EQUAL = 17;
    public final static int NONEQUAL = 18;
    public final static int MOREOREQUAL = 19;
    public final static int MORE = 20;
    public final static int SEMICOLON = 21;
    public final static int COMMA = 22;
    public final static int DOT = 23;
    public final static int COLON = 24;
}
/*
Program → main ( ) Block
Block → { Variables Statements }
Variables → Variables Variable | Variable
Variable → Type ID ;
Type → int | real | boolean
Statements → Statements ; Statement | Statement
Statement → Assignment | IfStatement
IfStatement → if ( RelExpression ) : Block ElsePart
ElsePart → ElifList ElseStatement | ElifList | ElseStatement | ε
ElifList → ElifList Elif | Elif
Elif → elif ( RelExpression ) : Block
ElseStatement → else : Block
RelExpression → Term RelOp Term | Term
Term → ID | CONST
RelOp → < | <= | == | <> | > | >=
Assignment → ID := Term
*/
