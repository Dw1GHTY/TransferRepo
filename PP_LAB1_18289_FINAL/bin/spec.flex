// import sekcija

%%

// Sekcija opcija i deklaracija
%class MPLexer
%function next_token
%line
%column
%debug
%type Yytoken

%eofval{
return new Yytoken( sym.EOF, null, yyline, yycolumn);
%eofval}

%{
//dodatni clanovi generisane klase
KWTable kwTable = new KWTable();
Yytoken getKW()
{
    return new Yytoken( kwTable.find( yytext() ),
    yytext(), yyline, yycolumn );
}

%}

//Stanja
%xstate KOMENTAR

//Makroi
slovo = [a-zA-Z]
cifra = [0-9]
%%

// pravila

\/\*\* { yybegin( KOMENTAR ); }
<KOMENTAR>~"*/" { yybegin( YYINITIAL ); }


//Tabulatori
[\t\n\r ] { ; }
\( { return new Yytoken( sym.OPEN_BRACKET, yytext(), yyline, yycolumn ); }
\) { return new Yytoken( sym.CLOSED_BRACKET, yytext(), yyline, yycolumn ); }
\{ { return new Yytoken( sym.OPEN_CURLY_BRACKET, yytext(), yyline, yycolumn ); }
\} { return new Yytoken( sym.CLOSED_CURLY_BRACKET, yytext(), yyline, yycolumn ); }

//Operatori
\< { return new Yytoken( sym.LESS,yytext(), yyline, yycolumn ); }
\<= { return new Yytoken( sym.LESSOREQUAL,yytext(), yyline, yycolumn ); }
== { return new Yytoken( sym.EQUAL,yytext(), yyline, yycolumn ); }
\<> { return new Yytoken( sym.NONEQUAL,yytext(), yyline, yycolumn ); }
> { return new Yytoken( sym.MORE,yytext(), yyline, yycolumn ); }
>= { return new Yytoken( sym.MOREOREQUAL,yytext(), yyline, yycolumn ); }

//Separatori
; { return new Yytoken( sym.SEMICOLON, yytext(), yyline, yycolumn ); }
: { return new Yytoken( sym.COLON, yytext(), yyline, yycolumn ); }
:= { return new Yytoken( sym.ASSIGNMENT, yytext(), yyline, yycolumn ); }
 
//bool
(true)|(false) { return new Yytoken( sym.BOOLEAN, yytext(), yyline, yycolumn ); }

//Kljucne reci
{slovo}+ { return getKW(); }

//Identifikatori
{slovo}({slovo}|{cifra})* { return new Yytoken(sym.ID, yytext(),yyline, yycolumn ); }

//Konstante
{cifra}\.{cifra}*(E[+-]{cifra}+)? { return new Yytoken( sym.REAL, yytext(), yyline, yycolumn ); }
#({cifra}|{slovo})+ { return new Yytoken( sym.INT, yytext(), yyline, yycolumn ); }
{cifra}+ { return new Yytoken( sym.INT, yytext(), yyline, yycolumn ); }


//Obrada gresaka
. { if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: " + yytext() ); }