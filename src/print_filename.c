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

bool char_to_octal(char str[5], char c)
{
	uint8_t nbr = (uint8_t)c;

	str[4] = '\0';
	str[3] = nbr % 8 + '0';
	nbr = nbr / 8;
	str[2] =  nbr % 8 + '0';
	nbr = nbr / 8;
	str[1] =  nbr % 8 + '0';
	str[0] =  '\\';

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

	size_t i = 0;
	while (str[i] != '\0')
	{
		if (char_need_quotes(str[i]))
			return true;
		
		i++;
	}

	return false;
}

size_t add_escapable_char(char c, char *str_dest)
{
	assert(char_need_to_be_escaped(c));

	if ( c >= 7 && c <= 13 )
	{
		switch (c)
		{
		case 7:
			ft_strcpy(str_dest, "\\a");
			return 2;

		case 8:
			ft_strcpy(str_dest, "\\b");
			return 2;

		case 9:
			ft_strcpy(str_dest, "\\t");
			return 2;

		case 10:
			ft_strcpy(str_dest, "\\n");
			return 2;

		case 11:
			ft_strcpy(str_dest, "\\v");
			return 2;

		case 12:
			ft_strcpy(str_dest, "\\f");
			return 2;

		case 13:
			ft_strcpy(str_dest, "\\r");
			return 2;
	
		default:
			return 0;
		}
	}
	else
	{
		char buff[5];
		char_to_octal(buff, c);
		ft_strcpy(str_dest, buff);
		return 4;
	}
}

char *dump_escaped_filename(char *original_filename)
{
	bool oct_mode = false;
	bool need_quotes = string_need_quotes(original_filename);
	char buffer[254 * 10] = {0};
	size_t i = 0; // in fn id
	size_t j = 0; // in buffer id
	
	if ( need_quotes == true )
	{
		buffer[j] = '\'';
		j++;
	}

	while (original_filename[i] != '\0' && j < sizeof(buffer) - 10 )
	{
		char current_parsed_char = original_filename[i];

		if (char_need_to_be_escaped(current_parsed_char))
		{
			if ( oct_mode == false )
			{
				ft_strcpy(&buffer[j], "'$'");
				j += 3;
				oct_mode = true;
			}

			j += add_escapable_char(current_parsed_char, &buffer[j]);
		}
		else
		{
			if ( oct_mode )
			{
				ft_strcpy(&buffer[j], "''");
				j += 2;
				oct_mode=false;
			}

			if (current_parsed_char == '\'')
			{
				ft_strcpy(&buffer[j], "''");
				j += 2;
			}
			else
			{
				buffer[j] = current_parsed_char;
				j++;
			}
		}
		i++;
	}

	if ( need_quotes == true )
	{
		buffer[j] = '\'';
		j++;
	}

	buffer[j] = '\0';
	return ft_strdup(buffer);

}