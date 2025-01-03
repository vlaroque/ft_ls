#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "libft.h"

#include "debug.h"
#include "entries_list.h"
#include "print_line.h"
#include "parse_args.h"
#include "entries_list_sort.h"

environment_t g_env = {0};

// void recursive_traversal(char *path, int flags)
//{
//	array_of_files = list_directory(path, flags);
//
//	print_list_of_files(array_of_files);
//
//	/* attention l'ordre des dossiers est impacté par -r ou -t */
//	for ( file in array_of_files )
//	{
//		if ( file is directory )
//			recursive_traversal(file->full_path, flags);
//	}
//
//	return;
// }

char *entry_normal_suffix_char(entry_t *entry)
{
	if (S_ISDIR(entry->stats.st_mode))
		return "/";
	else if (S_ISLNK(entry->stats.st_mode))
		return "@";
	else if (entry->stats.st_mode & S_IXUSR)
		return "*";
	else if (S_ISSOCK(entry->stats.st_mode))
		return "=";
	else if (S_ISFIFO(entry->stats.st_mode))
		return "|";
	return "";
}

void print_normal_format_line(entry_t *entry, environment_t *env)
{
	stream_cat(env->stream, entry->filename);
	stream_cat_end_of_line(env->stream, entry_normal_suffix_char(entry));
}

void remove_trailing_slashes(char *str)
{
	assert(str != NULL);

	size_t len = ft_strlen(str);

	if (len == 0)
		return;

	size_t last_idx = len - 1;

	while (str[last_idx] == '/')
	{
		str[last_idx] = '\0';
		last_idx--;
	}
}

char *file_path_cat(char *directory_path, char *file_name)
{
	assert(directory_path != NULL);
	assert(file_name != NULL);

	size_t dir_path_len = ft_strlen(directory_path);
	size_t file_name_len = ft_strlen(file_name);

	char *new_str = ft_strnew(dir_path_len + file_name_len + 2);
	if (new_str == NULL)
		return NULL;

	ft_strncpy(new_str, directory_path, dir_path_len);
	remove_trailing_slashes(new_str);
	ft_strncat(new_str, "/", 1);
	ft_strncat(new_str, file_name, file_name_len);

	return new_str;
}

bool explore_directory(char *path, entry_list_t *out_entry_list)
{
	DIR *dir_ptr = opendir(path);

	if (dir_ptr == NULL)
		return false;

	while (1)
	{
		struct dirent *dirent_ptr = readdir(dir_ptr);

		if (dirent_ptr == NULL)
			break;

		char *entry_path = file_path_cat(path, dirent_ptr->d_name);
		if (entry_path == NULL)
			return false;

		// no need to free entry_path here, now it was taken by the entry in entry_list
		entry_list_push_from_allocated_path(out_entry_list, entry_path);
	}

	closedir(dir_ptr);
	return true;
}

void print_entries_list(entry_list_t *entries, environment_t *env)
{
	entry_t *one_entry = entries->first;

	while (one_entry != NULL)
	{
		print_normal_format_line(one_entry, env);
		one_entry = one_entry->next;
	}
	stream_cat_end_of_line(env->stream, "");
}

void recursive_traversal(char *path, environment_t *env);

void explore_subdirectories(entry_list_t *entries, environment_t *env)
{
	entry_t *one_entry = entries->first;

	while (one_entry != NULL)
	{
		if (ft_strcmp(".", one_entry->filename) == 0 || ft_strcmp("..", one_entry->filename) == 0)
		{
			one_entry = one_entry->next;
			continue;
		}

		if (S_ISDIR(one_entry->stats.st_mode))
		{
			// stream_cat_end_of_line(env->stream, "");

			recursive_traversal(one_entry->full_path, env);
		}

		one_entry = one_entry->next;
	}
}

static print_dir_access_error(char *path)
{
	const char error_head[] = "ft_ls: cannot open directory '";

	const char error_tail[] = "'";
	char *err_str = ft_strnew(sizeof(error_head) + sizeof(error_tail) + ft_strlen(path) + 1);
	ft_strcat(err_str, error_head);
	ft_strcat(err_str, path);
	ft_strcat(err_str, error_tail);
	perror(err_str);
	ft_strdel(&err_str);
}

void recursive_traversal(char *path, environment_t *env)
{
	entry_list_t entries = {0};

	if (!explore_directory(path, &entries))
	{
		print_dir_access_error(path);
		return;
	}

	if (env->multiple_files || IS_FLAG_SET(env->flags, L_REC))
	{
		stream_cat(env->stream, path);
		stream_cat_end_of_line(env->stream, ":");
	}

	entries_list_qsort(entries.first, entries.last, compare_by_name);

	print_entries_list(&entries, env);

	if (IS_FLAG_SET(env->flags, L_REC))
	{
		explore_subdirectories(&entries, env);
	}
}

int main(int ac, char **av)
{
	if (!parse_args(&g_env, ac, av))
		return 1;

	g_env.stream = stream_init(STDOUT_FILENO);

	// printf("long_list = %b\n", IS_FLAG_SET(g_env.flags, L_LLO));
	// printf("recursive = %b\n", IS_FLAG_SET(g_env.flags, L_REC));
	// printf("all       = %b\n", IS_FLAG_SET(g_env.flags, L_ALL));
	// printf("reverse   = %b\n", IS_FLAG_SET(g_env.flags, L_REV));
	// printf("time sort = %b\n", IS_FLAG_SET(g_env.flags, L_TMS));
	// printf("muliple_files = %b\n", g_env.multiple_files);
	// debug_entry_list(&g_env.root_entries_list);

	entry_t *entry = g_env.root_entries_list.first;

	while (entry != NULL)
	{
		recursive_traversal(entry->full_path, &g_env);
		entry = entry->next;
		if (entry != NULL)
		{
			stream_cat_end_of_line(g_env.stream, "");
		}
	}

	stream_close(g_env.stream);

	return 0;
}
