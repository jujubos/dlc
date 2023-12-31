%{
#undef YY_INPUT
#define YY_INPUT(buf, result, max_size) (result = my_yyinput(buf, max_size))
#include <stdio.h>
#include <string.h>
#include "DBG.h"
#include "decls.h"
#include "y.tab.h"

static int
file_input(char *buf, int max_size)
{
    int ch;
    int len;

    if (feof(yyin))
        return 0;

    for (len = 0; len < max_size; len++) {
        ch = getc(yyin);
        if (ch == EOF)
            break;
        buf[len] = ch;
    }
    return len;
}

static char **st_source_string;
static int st_current_source_line;
static int st_current_char_index;
 
// void
// dkc_set_source_string(char **source)
// {
//     st_source_string = source;
//     st_current_source_line = 0;
//     st_current_char_index = 0;
// }

static int
string_input(char *buf, int max_size)
{
    int len;

    if (st_source_string[st_current_source_line] == NULL)
        return 0;

    if (st_source_string[st_current_source_line][st_current_char_index]
        == '\0') {
        st_current_source_line++;
        st_current_char_index = 0;
    }

    if (st_source_string[st_current_source_line] == NULL)
        return 0;

    len = smaller(strlen(st_source_string[st_current_source_line])
                  - st_current_char_index,
                  max_size);
    strncpy(buf,
            &st_source_string[st_current_source_line][st_current_char_index],
            len);
    st_current_char_index += len;

    return len;
}

static int
my_yyinput(char *buf, int max_size)
{
    int result;
    result = file_input(buf, max_size);

    // switch (dkc_get_current_compiler()->input_mode) {
    // case DKC_FILE_INPUT_MODE:
    //     result = file_input(buf, max_size);
    //     break;
    // case DKC_STRING_INPUT_MODE:
    //     result = string_input(buf, max_size);
    //     break;
    // default:
    //     DBG_panic(("bad default. input_mode..%d\n",
    //                dkc_get_current_compiler()->input_mode));
    // }

    return result;
}


int
yywrap(void)
{
    return 1;
}

static void
increment_line_number(void)
{
    get_current_compiler()->current_line_number++;
}
%}
%start C_COMMENT CC_COMMENT STRING_LITERAL_STATE
%%
<INITIAL>"if"           return IF;
<INITIAL>"else"         return ELSE;
<INITIAL>"elsif"        return ELSIF;
<INITIAL>"while"        return WHILE;
<INITIAL>"for"          return FOR;
<INITIAL>"foreach"      return FOREACH;
<INITIAL>"return"       return RETURN_T;
<INITIAL>"break"        return BREAK;
<INITIAL>"continue"     return CONTINUE;
<INITIAL>"true"         return TRUE_T;
<INITIAL>"false"        return FALSE_T;
<INITIAL>"try"          return TRY;
<INITIAL>"catch"        return CATCH;
<INITIAL>"finally"      return FINALLY;
<INITIAL>"throw"        return THROW;
<INITIAL>"new"          return NEW;
<INITIAL>"boolean"      return BOOLEAN_T;
<INITIAL>"int"          return INT_T;
<INITIAL>"double"       return DOUBLE_T;
<INITIAL>"string"       return STRING_T;
<INITIAL>"NULL"         return NULL_T;
<INITIAL>"("            return LP;
<INITIAL>")"            return RP;
<INITIAL>"["            return LB;
<INITIAL>"]"            return RB;
<INITIAL>"{"            return LC;
<INITIAL>"}"            return RC;
<INITIAL>";"            return SEMICOLON;
<INITIAL>":"            return COLON;
<INITIAL>","            return COMMA;
<INITIAL>"&&"           return LOGICAL_AND;
<INITIAL>"||"           return LOGICAL_OR;
<INITIAL>"="            return ASSIGN_T;
<INITIAL>"=="           return EQ;
<INITIAL>"!="           return NE;
<INITIAL>">"            return GT;
<INITIAL>">="           return GE;
<INITIAL>"<"            return LT;
<INITIAL>"<="           return LE;
<INITIAL>"+"            return ADD;
<INITIAL>"-"            return SUB;
<INITIAL>"*"            return MUL;
<INITIAL>"/"            return DIV;
<INITIAL>"%"            return MOD;
<INITIAL>"+="           return ADD_ASSIGN_T;
<INITIAL>"-="           return SUB_ASSIGN_T;
<INITIAL>"*="           return MUL_ASSIGN_T;
<INITIAL>"/="           return DIV_ASSIGN_T;
<INITIAL>"%="           return MOD_ASSIGN_T;
<INITIAL>"++"           return INCREMENT;
<INITIAL>"--"           return DECREMENT;
<INITIAL>"!"            return EXCLAMATION;
<INITIAL>"."            return DOT;
<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
    yylval.identifier = create_identifier(yytext);
    return IDENTIFIER;
}
<INITIAL>[1-9][0-9]* {
    Expression  *expression = alloc_expression(INT_LITERAL_EXPRESSION);
    expression->type = create_typespecifier(INT_TYPE);
    sscanf(yytext, "%d", &expression->int_v);
    yylval.expression = expression;
    return INT_LITERAL;
}
<INITIAL>"0" {
    Expression  *expression = alloc_expression(INT_LITERAL_EXPRESSION);
    expression->type = create_typespecifier(INT_TYPE);
    expression->int_v = 0;
    yylval.expression = expression;
    return INT_LITERAL;
}
<INITIAL>[0-9]+\.[0-9]+ {
    Expression  *expression = alloc_expression(DOUBLE_LITERAL_EXPRESSION);
    expression->type = create_typespecifier(DOUBLE_TYPE);
    sscanf(yytext, "%lf", &expression->double_v);
    yylval.expression = expression;
    return DOUBLE_LITERAL;
}
<INITIAL>\" {
    open_string_literal();
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>[ \t] ;
<INITIAL>[ \t\r\n] {increment_line_number();}
<INITIAL>"/*"     BEGIN C_COMMENT;
<INITIAL>"//"     BEGIN CC_COMMENT;
<INITIAL>.      {
    char buf[LINE_BUF_SIZE];

    if (isprint(yytext[0])) {
        buf[0] = yytext[0];
        buf[1] = '\0';
    } else {
        sprintf(buf, "0x%02x", (unsigned char)yytext[0]);
    }
    printf("diksam.l -- line 192 error\n");
    exit(1);
    // dkc_compile_error(dkc_get_current_compiler()->current_line_number,
    //                   CHARACTER_INVALID_ERR,
    //                   STRING_MESSAGE_ARGUMENT, "bad_char", buf,
    //                   MESSAGE_ARGUMENT_END);
}
<C_COMMENT>\n     increment_line_number();
<C_COMMENT>"*/"     {
    BEGIN INITIAL;
}
<C_COMMENT>.      ;
<CC_COMMENT>\n  {
    increment_line_number();
    BEGIN INITIAL;
}
<CC_COMMENT>.   ;
<STRING_LITERAL_STATE>\"        {
    Expression *expression = alloc_expression(STRING_LITERAL_EXPRESSION);
    expression->type = create_typespecifier(STRING_TYPE);
    expression->string_v = close_string_literal();
    yylval.expression = expression;
    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\n        {
    add_string_literal('\n');
    increment_line_number();
}
<STRING_LITERAL_STATE>\\\"      add_string_literal('"');
<STRING_LITERAL_STATE>\\n       add_string_literal('\n');
<STRING_LITERAL_STATE>\\t       add_string_literal('\t');
<STRING_LITERAL_STATE>\\\\      add_string_literal('\\');
<STRING_LITERAL_STATE>.         {
    add_string_literal(yytext[0]);
}
%%
