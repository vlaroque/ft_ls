#include "print_filename.h"

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#include "libft.h"


bool copy_as_single_char_in_printable_filename(char c)
{
	return ( ( 32 <= c && c <= 38 ) || ( 40 <= c && c <= 126 ));
}


/* here we really speak about the '$'\\001 kind of escape */
bool char_need_to_be_escaped(char c)
{
	return ( c < ' ' || c > '~' );
}

bool char_to_octal(char str[4], char c)
{
	uint8_t nbr = (uint8_t)c;

	str[3] = '\0';
	str[2] = nbr % 8 + '0';
	nbr = nbr / 8;
	str[1] =  nbr % 8 + '0';
	nbr = nbr / 8;
	str[0] =  nbr % 8 + '0';

	return true;
}

bool char_need_quotes(char c)
{
	if ( char_need_to_be_escaped(c) )
		return true;

	if ( ft_isalnum(c) )
		return false;
	
	if ( c == '#'
	     || c == '%'
	     || c == '+'
	     || c == ','
	     || c == '-'
	     || c == '.'
	     || c == ':'
	     || c == ']'
	     || c == '_'
	     || c == '{'
	     || c == '}'
	     || c == '~'
		 )
		return false;
	
	return true;

}

bool string_need_quotes(char *str)
{
	assert(str != NULL);

	while (str != NULL)
	{
		if (char_need_quotes(*str))
			return true;
	}
	return false;
}

to_printable_t *give_printable_for_char(char c)
{
	static to_printable_t table[] = {
		[0]   = { "",         sizeof(""),         NONE_QUOTE},
		[1]   = { "'$'\\001", sizeof("'$'\\001"), SIMPLE_QUOTES},
		[2]   = { "'$'\\002", sizeof("'$'\\002"), SIMPLE_QUOTES},
		[3]   = { "'$'\\003", sizeof("'$'\\003"), SIMPLE_QUOTES},
		[4]   = { "'$'\\004", sizeof("'$'\\004"), SIMPLE_QUOTES},
		[5]   = { "'$'\\005", sizeof("'$'\\005"), SIMPLE_QUOTES},
		[6]   = { "'$'\\006", sizeof("'$'\\006"), SIMPLE_QUOTES},
		[7]   = { "'$'\\a",   sizeof("'$'\\a"),   SIMPLE_QUOTES},
		[8]   = { "'$'\\b",   sizeof("'$'\\b"),   SIMPLE_QUOTES},
		[9]   = { "'$'\\t",   sizeof("'$'\\t"),   SIMPLE_QUOTES},
		[10]  = { "'$'\\n",   sizeof("'$'\\n"),   SIMPLE_QUOTES},
		[11]  = { "'$'\\v",   sizeof("'$'\\v"),   SIMPLE_QUOTES},
		[12]  = { "'$'\\f",   sizeof("'$'\\f"),   SIMPLE_QUOTES},
		[13]  = { "'$'\\r",   sizeof("'$'\\r"),   SIMPLE_QUOTES},
		[14]  = { "'$'\\016", sizeof("'$'\\016"), SIMPLE_QUOTES},
		[15]  = { "'$'\\017", sizeof("'$'\\017"), SIMPLE_QUOTES},
		[16]  = { "'$'\\020", sizeof("'$'\\020"), SIMPLE_QUOTES},
		[17]  = { "'$'\\021", sizeof("'$'\\021"), SIMPLE_QUOTES},
		[18]  = { "'$'\\022", sizeof("'$'\\022"), SIMPLE_QUOTES},
		[19]  = { "'$'\\023", sizeof("'$'\\023"), SIMPLE_QUOTES},
		[20]  = { "'$'\\024", sizeof("'$'\\024"), SIMPLE_QUOTES},
		[21]  = { "'$'\\025", sizeof("'$'\\025"), SIMPLE_QUOTES},
		[22]  = { "'$'\\026", sizeof("'$'\\026"), SIMPLE_QUOTES},
		[23]  = { "'$'\\027", sizeof("'$'\\027"), SIMPLE_QUOTES},
		[24]  = { "'$'\\030", sizeof("'$'\\030"), SIMPLE_QUOTES},
		[25]  = { "'$'\\031", sizeof("'$'\\031"), SIMPLE_QUOTES},
		[26]  = { "'$'\\032", sizeof("'$'\\032"), SIMPLE_QUOTES},
		[27]  = { "'$'\\033", sizeof("'$'\\033"), SIMPLE_QUOTES},
		[28]  = { "'$'\\034", sizeof("'$'\\034"), SIMPLE_QUOTES},
		[29]  = { "'$'\\035", sizeof("'$'\\035"), SIMPLE_QUOTES},
		[30]  = { "'$'\\036", sizeof("'$'\\036"), SIMPLE_QUOTES},
		[31]  = { "'$'\\037", sizeof("'$'\\037"), SIMPLE_QUOTES},
		[32]  = { " ",       sizeof(" "),         SIMPLE_QUOTES},
		[33]  = { "!",       sizeof("!"),         SIMPLE_QUOTES},
		[34]  = { "\"",      sizeof("\""),        SIMPLE_QUOTES},
		[35]  = { "#",       sizeof("#"),         NONE_QUOTE},
		[36]  = { "$",       sizeof("$"),         SIMPLE_QUOTES},
		[37]  = { "%",       sizeof("%"),         NONE_QUOTE},
		[38]  = { "&",       sizeof("&"),         SIMPLE_QUOTES},
	/*	[39]  = { "'",       sizeof("'"),         DOUBLE_QUOTES}, */
		[39]  = { "\\'",     sizeof("\\'"),       SIMPLE_QUOTES}, /* has been modified to deal with it efficiently */
		[40]  = { "(",       sizeof("("),         SIMPLE_QUOTES},
		[41]  = { ")",       sizeof(")"),         SIMPLE_QUOTES},
		[42]  = { "*",       sizeof("*"),         SIMPLE_QUOTES},
		[43]  = { "+",       sizeof("+"),         NONE_QUOTE},
		[44]  = { ",",       sizeof(","),         NONE_QUOTE},
		[45]  = { "-",       sizeof("-"),         NONE_QUOTE},
		[46]  = { ".",       sizeof("."),         NONE_QUOTE},
		[47]  = { "/",       sizeof("/"),         NONE_QUOTE}, /* must never be in path */
		[48]  = { "0",       sizeof("0"),         NONE_QUOTE},
		[49]  = { "1",       sizeof("1"),         NONE_QUOTE},
		[50]  = { "2",       sizeof("2"),         NONE_QUOTE},
		[51]  = { "3",       sizeof("3"),         NONE_QUOTE},
		[52]  = { "4",       sizeof("4"),         NONE_QUOTE},
		[53]  = { "5",       sizeof("5"),         NONE_QUOTE},
		[54]  = { "6",       sizeof("6"),         NONE_QUOTE},
		[55]  = { "7",       sizeof("7"),         NONE_QUOTE},
		[56]  = { "8",       sizeof("8"),         NONE_QUOTE},
		[57]  = { "9",       sizeof("9"),         NONE_QUOTE},
		[58]  = { ":",       sizeof(":"),         NONE_QUOTE},
		[59]  = { ";",       sizeof(";"),         SIMPLE_QUOTES},
		[60]  = { "<",       sizeof("<"),         SIMPLE_QUOTES},
		[61]  = { "=",       sizeof("="),         SIMPLE_QUOTES},
		[62]  = { ">",       sizeof(">"),         SIMPLE_QUOTES},
		[63]  = { "?",       sizeof("?"),         SIMPLE_QUOTES},
		[64]  = { "@",       sizeof("@"),         SIMPLE_QUOTES},
		[65]  = { "A",       sizeof("A"),         NONE_QUOTE},
		[66]  = { "B",       sizeof("B"),         NONE_QUOTE},
		[67]  = { "C",       sizeof("C"),         NONE_QUOTE},
		[68]  = { "D",       sizeof("D"),         NONE_QUOTE},
		[69]  = { "E",       sizeof("E"),         NONE_QUOTE},
		[70]  = { "F",       sizeof("F"),         NONE_QUOTE},
		[71]  = { "G",       sizeof("G"),         NONE_QUOTE},
		[72]  = { "H",       sizeof("H"),         NONE_QUOTE},
		[73]  = { "I",       sizeof("I"),         NONE_QUOTE},
		[74]  = { "J",       sizeof("J"),         NONE_QUOTE},
		[75]  = { "K",       sizeof("K"),         NONE_QUOTE},
		[76]  = { "L",       sizeof("L"),         NONE_QUOTE},
		[77]  = { "M",       sizeof("M"),         NONE_QUOTE},
		[78]  = { "N",       sizeof("N"),         NONE_QUOTE},
		[79]  = { "O",       sizeof("O"),         NONE_QUOTE},
		[80]  = { "P",       sizeof("P"),         NONE_QUOTE},
		[81]  = { "Q",       sizeof("Q"),         NONE_QUOTE},
		[82]  = { "R",       sizeof("R"),         NONE_QUOTE},
		[83]  = { "S",       sizeof("S"),         NONE_QUOTE},
		[84]  = { "T",       sizeof("T"),         NONE_QUOTE},
		[85]  = { "U",       sizeof("U"),         NONE_QUOTE},
		[86]  = { "V",       sizeof("V"),         NONE_QUOTE},
		[87]  = { "W",       sizeof("W"),         NONE_QUOTE},
		[88]  = { "X",       sizeof("X"),         NONE_QUOTE},
		[89]  = { "Y",       sizeof("Y"),         NONE_QUOTE},
		[90]  = { "Z",       sizeof("Z"),         NONE_QUOTE},
		[91]  = { "[",       sizeof("["),         SIMPLE_QUOTES},
		[92]  = { "\\",      sizeof("\\"),        SIMPLE_QUOTES},
		[93]  = { "]",       sizeof("]"),         NONE_QUOTE},
		[94]  = { "^",       sizeof("^"),         SIMPLE_QUOTES},
		[95]  = { "_",       sizeof("_"),         NONE_QUOTE},
		[96]  = { "`",       sizeof("`"),         SIMPLE_QUOTES},
		[97]  = { "a",       sizeof("a"),         NONE_QUOTE},
		[98]  = { "b",       sizeof("b"),         NONE_QUOTE},
		[99]  = { "c",       sizeof("c"),         NONE_QUOTE},
		[100] = { "d",       sizeof("d"),       NONE_QUOTE},
		[101] = { "e",       sizeof("e"),       NONE_QUOTE},
		[102] = { "f",       sizeof("f"),       NONE_QUOTE},
		[103] = { "g",       sizeof("g"),       NONE_QUOTE},
		[104] = { "h",       sizeof("h"),       NONE_QUOTE},
		[105] = { "i",       sizeof("i"),       NONE_QUOTE},
		[106] = { "j",       sizeof("j"),       NONE_QUOTE},
		[107] = { "k",       sizeof("k"),       NONE_QUOTE},
		[108] = { "l",       sizeof("l"),       NONE_QUOTE},
		[109] = { "m",       sizeof("m"),       NONE_QUOTE},
		[110] = { "n",       sizeof("n"),       NONE_QUOTE},
		[111] = { "o",       sizeof("o"),       NONE_QUOTE},
		[112] = { "p",       sizeof("p"),       NONE_QUOTE},
		[113] = { "q",       sizeof("q"),       NONE_QUOTE},
		[114] = { "r",       sizeof("r"),       NONE_QUOTE},
		[115] = { "s",       sizeof("s"),       NONE_QUOTE},
		[116] = { "t",       sizeof("t"),       NONE_QUOTE},
		[117] = { "u",       sizeof("u"),       NONE_QUOTE},
		[118] = { "v",       sizeof("v"),       NONE_QUOTE},
		[119] = { "w",       sizeof("w"),       NONE_QUOTE},
		[120] = { "x",       sizeof("x"),       NONE_QUOTE},
		[121] = { "y",       sizeof("y"),       NONE_QUOTE},
		[122] = { "z",       sizeof("z"),       NONE_QUOTE},
		[123] = { "{",       sizeof("{"),       NONE_QUOTE},
		[124] = { "|",       sizeof("|"),       SIMPLE_QUOTES},
		[125] = { "}",       sizeof("}"),       NONE_QUOTE },
		[126] = { "~",       sizeof("~"),       NONE_QUOTE },
		[127] = {"'$'\\177", sizeof("'$'\\177"), SIMPLE_QUOTES},
		[128] = {"'$'\\200", sizeof("'$'\\200"), SIMPLE_QUOTES},
		[129] = {"'$'\\201", sizeof("'$'\\201"), SIMPLE_QUOTES},
		[130] = {"'$'\\202", sizeof("'$'\\202"), SIMPLE_QUOTES},
		[131] = {"'$'\\203", sizeof("'$'\\203"), SIMPLE_QUOTES},
		[132] = {"'$'\\204", sizeof("'$'\\204"), SIMPLE_QUOTES},
		[133] = {"'$'\\205", sizeof("'$'\\205"), SIMPLE_QUOTES},
		[134] = {"'$'\\206", sizeof("'$'\\206"), SIMPLE_QUOTES},
		[135] = {"'$'\\207", sizeof("'$'\\207"), SIMPLE_QUOTES},
		[136] = {"'$'\\210", sizeof("'$'\\210"), SIMPLE_QUOTES},
		[137] = {"'$'\\211", sizeof("'$'\\211"), SIMPLE_QUOTES},
		[138] = {"'$'\\212", sizeof("'$'\\212"), SIMPLE_QUOTES},
		[139] = {"'$'\\213", sizeof("'$'\\213"), SIMPLE_QUOTES},
		[140] = {"'$'\\214", sizeof("'$'\\214"), SIMPLE_QUOTES},
		[141] = {"'$'\\215", sizeof("'$'\\215"), SIMPLE_QUOTES},
		[142] = {"'$'\\216", sizeof("'$'\\216"), SIMPLE_QUOTES},
		[143] = {"'$'\\217", sizeof("'$'\\217"), SIMPLE_QUOTES},
		[144] = {"'$'\\220", sizeof("'$'\\220"), SIMPLE_QUOTES},
		[145] = {"'$'\\221", sizeof("'$'\\221"), SIMPLE_QUOTES},
		[146] = {"'$'\\222", sizeof("'$'\\222"), SIMPLE_QUOTES},
		[147] = {"'$'\\223", sizeof("'$'\\223"), SIMPLE_QUOTES},
		[148] = {"'$'\\224", sizeof("'$'\\224"), SIMPLE_QUOTES},
		[149] = {"'$'\\225", sizeof("'$'\\225"), SIMPLE_QUOTES},
		[150] = {"'$'\\226", sizeof("'$'\\226"), SIMPLE_QUOTES},
		[151] = {"'$'\\227", sizeof("'$'\\227"), SIMPLE_QUOTES},
		[152] = {"'$'\\230", sizeof("'$'\\230"), SIMPLE_QUOTES},
		[153] = {"'$'\\231", sizeof("'$'\\231"), SIMPLE_QUOTES},
		[154] = {"'$'\\232", sizeof("'$'\\232"), SIMPLE_QUOTES},
		[155] = {"'$'\\233", sizeof("'$'\\233"), SIMPLE_QUOTES},
		[156] = {"'$'\\234", sizeof("'$'\\234"), SIMPLE_QUOTES},
		[157] = {"'$'\\235", sizeof("'$'\\235"), SIMPLE_QUOTES},
		[158] = {"'$'\\236", sizeof("'$'\\236"), SIMPLE_QUOTES},
		[159] = {"'$'\\237", sizeof("'$'\\237"), SIMPLE_QUOTES},
		[160] = {"'$'\\240", sizeof("'$'\\240"), SIMPLE_QUOTES},
		[161] = {"'$'\\241", sizeof("'$'\\241"), SIMPLE_QUOTES},
		[162] = {"'$'\\242", sizeof("'$'\\242"), SIMPLE_QUOTES},
		[163] = {"'$'\\243", sizeof("'$'\\243"), SIMPLE_QUOTES},
		[164] = {"'$'\\244", sizeof("'$'\\244"), SIMPLE_QUOTES},
		[165] = {"'$'\\245", sizeof("'$'\\245"), SIMPLE_QUOTES},
		[166] = {"'$'\\246", sizeof("'$'\\246"), SIMPLE_QUOTES},
		[167] = {"'$'\\247", sizeof("'$'\\247"), SIMPLE_QUOTES},
		[168] = {"'$'\\250", sizeof("'$'\\250"), SIMPLE_QUOTES},
		[169] = {"'$'\\251", sizeof("'$'\\251"), SIMPLE_QUOTES},
		[170] = {"'$'\\252", sizeof("'$'\\252"), SIMPLE_QUOTES},
		[171] = {"'$'\\253", sizeof("'$'\\253"), SIMPLE_QUOTES},
		[172] = {"'$'\\254", sizeof("'$'\\254"), SIMPLE_QUOTES},
		[173] = {"'$'\\255", sizeof("'$'\\255"), SIMPLE_QUOTES},
		[174] = {"'$'\\256", sizeof("'$'\\256"), SIMPLE_QUOTES},
		[175] = {"'$'\\257", sizeof("'$'\\257"), SIMPLE_QUOTES},
		[176] = {"'$'\\260", sizeof("'$'\\260"), SIMPLE_QUOTES},
		[177] = {"'$'\\261", sizeof("'$'\\261"), SIMPLE_QUOTES},
		[178] = {"'$'\\262", sizeof("'$'\\262"), SIMPLE_QUOTES},
		[179] = {"'$'\\263", sizeof("'$'\\263"), SIMPLE_QUOTES},
		[180] = {"'$'\\264", sizeof("'$'\\264"), SIMPLE_QUOTES},
		[181] = {"'$'\\265", sizeof("'$'\\265"), SIMPLE_QUOTES},
		[182] = {"'$'\\266", sizeof("'$'\\266"), SIMPLE_QUOTES},
		[183] = {"'$'\\267", sizeof("'$'\\267"), SIMPLE_QUOTES},
		[184] = {"'$'\\270", sizeof("'$'\\270"), SIMPLE_QUOTES},
		[185] = {"'$'\\271", sizeof("'$'\\271"), SIMPLE_QUOTES},
		[186] = {"'$'\\272", sizeof("'$'\\272"), SIMPLE_QUOTES},
		[187] = {"'$'\\273", sizeof("'$'\\273"), SIMPLE_QUOTES},
		[188] = {"'$'\\274", sizeof("'$'\\274"), SIMPLE_QUOTES},
		[189] = {"'$'\\275", sizeof("'$'\\275"), SIMPLE_QUOTES},
		[190] = {"'$'\\276", sizeof("'$'\\276"), SIMPLE_QUOTES},
		[191] = {"'$'\\277", sizeof("'$'\\277"), SIMPLE_QUOTES},
		[192] = {"'$'\\300", sizeof("'$'\\300"), SIMPLE_QUOTES},
		[193] = {"'$'\\301", sizeof("'$'\\301"), SIMPLE_QUOTES},
		[194] = {"'$'\\302", sizeof("'$'\\302"), SIMPLE_QUOTES},
		[195] = {"'$'\\303", sizeof("'$'\\303"), SIMPLE_QUOTES},
		[196] = {"'$'\\304", sizeof("'$'\\304"), SIMPLE_QUOTES},
		[197] = {"'$'\\305", sizeof("'$'\\305"), SIMPLE_QUOTES},
		[198] = {"'$'\\306", sizeof("'$'\\306"), SIMPLE_QUOTES},
		[199] = {"'$'\\307", sizeof("'$'\\307"), SIMPLE_QUOTES},
		[200] = {"'$'\\310", sizeof("'$'\\310"), SIMPLE_QUOTES},
		[201] = {"'$'\\311", sizeof("'$'\\311"), SIMPLE_QUOTES},
		[202] = {"'$'\\312", sizeof("'$'\\312"), SIMPLE_QUOTES},
		[203] = {"'$'\\313", sizeof("'$'\\313"), SIMPLE_QUOTES},
		[204] = {"'$'\\314", sizeof("'$'\\314"), SIMPLE_QUOTES},
		[205] = {"'$'\\315", sizeof("'$'\\315"), SIMPLE_QUOTES},
		[206] = {"'$'\\316", sizeof("'$'\\316"), SIMPLE_QUOTES},
		[207] = {"'$'\\317", sizeof("'$'\\317"), SIMPLE_QUOTES},
		[208] = {"'$'\\320", sizeof("'$'\\320"), SIMPLE_QUOTES},
		[209] = {"'$'\\321", sizeof("'$'\\321"), SIMPLE_QUOTES},
		[210] = {"'$'\\322", sizeof("'$'\\322"), SIMPLE_QUOTES},
		[211] = {"'$'\\323", sizeof("'$'\\323"), SIMPLE_QUOTES},
		[212] = {"'$'\\324", sizeof("'$'\\324"), SIMPLE_QUOTES},
		[213] = {"'$'\\325", sizeof("'$'\\325"), SIMPLE_QUOTES},
		[214] = {"'$'\\326", sizeof("'$'\\326"), SIMPLE_QUOTES},
		[215] = {"'$'\\327", sizeof("'$'\\327"), SIMPLE_QUOTES},
		[216] = {"'$'\\330", sizeof("'$'\\330"), SIMPLE_QUOTES},
		[217] = {"'$'\\331", sizeof("'$'\\331"), SIMPLE_QUOTES},
		[218] = {"'$'\\332", sizeof("'$'\\332"), SIMPLE_QUOTES},
		[219] = {"'$'\\333", sizeof("'$'\\333"), SIMPLE_QUOTES},
		[220] = {"'$'\\334", sizeof("'$'\\334"), SIMPLE_QUOTES},
		[221] = {"'$'\\335", sizeof("'$'\\335"), SIMPLE_QUOTES},
		[222] = {"'$'\\336", sizeof("'$'\\336"), SIMPLE_QUOTES},
		[223] = {"'$'\\337", sizeof("'$'\\337"), SIMPLE_QUOTES},
		[224] = {"'$'\\340", sizeof("'$'\\340"), SIMPLE_QUOTES},
		[225] = {"'$'\\341", sizeof("'$'\\341"), SIMPLE_QUOTES},
		[226] = {"'$'\\342", sizeof("'$'\\342"), SIMPLE_QUOTES},
		[227] = {"'$'\\343", sizeof("'$'\\343"), SIMPLE_QUOTES},
		[228] = {"'$'\\344", sizeof("'$'\\344"), SIMPLE_QUOTES},
		[229] = {"'$'\\345", sizeof("'$'\\345"), SIMPLE_QUOTES},
		[230] = {"'$'\\346", sizeof("'$'\\346"), SIMPLE_QUOTES},
		[231] = {"'$'\\347", sizeof("'$'\\347"), SIMPLE_QUOTES},
		[232] = {"'$'\\350", sizeof("'$'\\350"), SIMPLE_QUOTES},
		[233] = {"'$'\\351", sizeof("'$'\\351"), SIMPLE_QUOTES},
		[234] = {"'$'\\352", sizeof("'$'\\352"), SIMPLE_QUOTES},
		[235] = {"'$'\\353", sizeof("'$'\\353"), SIMPLE_QUOTES},
		[236] = {"'$'\\354", sizeof("'$'\\354"), SIMPLE_QUOTES},
		[237] = {"'$'\\355", sizeof("'$'\\355"), SIMPLE_QUOTES},
		[238] = {"'$'\\356", sizeof("'$'\\356"), SIMPLE_QUOTES},
		[239] = {"'$'\\357", sizeof("'$'\\357"), SIMPLE_QUOTES},
		[240] = {"'$'\\360", sizeof("'$'\\360"), SIMPLE_QUOTES},
		[241] = {"'$'\\361", sizeof("'$'\\361"), SIMPLE_QUOTES},
		[242] = {"'$'\\362", sizeof("'$'\\362"), SIMPLE_QUOTES},
		[243] = {"'$'\\363", sizeof("'$'\\363"), SIMPLE_QUOTES},
		[244] = {"'$'\\364", sizeof("'$'\\364"), SIMPLE_QUOTES},
		[245] = {"'$'\\365", sizeof("'$'\\365"), SIMPLE_QUOTES},
		[246] = {"'$'\\366", sizeof("'$'\\366"), SIMPLE_QUOTES},
		[247] = {"'$'\\367", sizeof("'$'\\367"), SIMPLE_QUOTES},
		[248] = {"'$'\\370", sizeof("'$'\\370"), SIMPLE_QUOTES},
		[249] = {"'$'\\371", sizeof("'$'\\371"), SIMPLE_QUOTES},
		[250] = {"'$'\\372", sizeof("'$'\\372"), SIMPLE_QUOTES},
		[251] = {"'$'\\373", sizeof("'$'\\373"), SIMPLE_QUOTES},
		[252] = {"'$'\\374", sizeof("'$'\\374"), SIMPLE_QUOTES},
		[253] = {"'$'\\375", sizeof("'$'\\375"), SIMPLE_QUOTES},
		[254] = {"'$'\\376", sizeof("'$'\\376"), SIMPLE_QUOTES},
		[255] = {"'$'\\377", sizeof("'$'\\377"), SIMPLE_QUOTES},
};

	return &table[(size_t)c];
}

/*
void printable_str_len(char *str)
{
	size_t i = 0;
	bool need_for_quotes = false;
	bool 

	while ( str[i] != NULL )
	{

	}
	
}
*/

/*
char *escape_and_quote(const char *filename)
{
	size_t filename_len = ft_strlen(filename);
	bool need_for_quotes = false;

	char *printable_filename = ft_strnew(filename_len * 7 + 3);
	
	if (printable_filename == NULL)
		return NULL;

	size_t index_real_fn = 0;
	size_t index_printable_fn = 0;

	if ( need_for_quotes == true)
		printable_filename[index_printable_fn++] = '\'';

	while( index_real_fn < filename_len )
	{
		if ( copy_as_single_char_in_printable_filename(filename[index_real_fn]) )
			printable_filename[index_printable_fn++] = filename[index_real_fn];
		else
		{
			to_printable_t *printbl = give_printable_for_char(filename[index_real_fn]);
			ft_strcpy(&printable_filename[index_printable_fn], printbl->printable);
			index_printable_fn += printbl->len;
		}

		index_real_fn++;
	}

	if ( need_for_quotes == true)
		printable_filename[index_printable_fn++] = '\'';

	printable_filename[index_printable_fn++] = '\0'; // < final \0
	return printable_filename;
}

*/

