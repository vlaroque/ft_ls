#include "print.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

#include "libft.h"
#include "print_filename.h"

/*
static char *entry_normal_suffix_char(entry_t *entry, environment_t *env)
{
	if (S_ISDIR(entry->stats.st_mode))
		return "/";
	else if (S_ISLNK(entry->stats.st_mode))
	{
		if (IS_FLAG_SET(env->flags, L_LLO))
			return "";
		else
			return "@";
	}
	else if (entry->stats.st_mode & S_IXUSR)
		return "*";
	else if (S_ISSOCK(entry->stats.st_mode))
		return "=";
	else if (S_ISFIFO(entry->stats.st_mode))
		return "|";
	return "";
}
*/

void print_normal_format_line(entry_t *entry, environment_t *env)
{
	stream_cat_end_of_line(env->stream, entry->printable_filename);
	//stream_cat_end_of_line(env->stream, entry_normal_suffix_char(entry, env));
}

void set_permissions_str(char str[11], mode_t mode)
{
	if (S_ISDIR(mode))
		str[0] = 'd';
	else if (S_ISLNK(mode))
		str[0] = 'l';
	else if (S_ISCHR(mode))
		str[0] = 'c';
	else if (S_ISBLK(mode))
		str[0] = 'b';
	else if (S_ISFIFO(mode))
		str[0] = 'p';
	else if (S_ISSOCK(mode))
		str[0] = 's';
	else
		str[0] = '-';

	/* Owner permissions */
	str[1] = (mode & S_IRUSR) ? 'r' : '-';
	str[2] = (mode & S_IWUSR) ? 'w' : '-';
	str[3] = (mode & S_IXUSR) ? 'x' : '-';
	/* Group permissions */
	str[4] = (mode & S_IRGRP) ? 'r' : '-';
	str[5] = (mode & S_IWGRP) ? 'w' : '-';
	str[6] = (mode & S_IXGRP) ? 'x' : '-';
	/* Other permissions */
	str[7] = (mode & S_IROTH) ? 'r' : '-';
	str[8] = (mode & S_IWOTH) ? 'w' : '-';
	str[9] = (mode & S_IXOTH) ? 'x' : '-';

	str[10] = '\0';
}

static void print_nlinks(entry_t *entry, environment_t *env)
{
	char *nlinks = ft_ulongtoa(entry->stats.st_nlink);

	if (nlinks == NULL)
	{
		stream_cat(env->stream, "? ");
		return;
	}

	stream_cat(env->stream, nlinks);
	free(nlinks);
	stream_cat(env->stream, " ");
}

static void print_size(entry_t *entry, environment_t *env)
{
	char *size = ft_ulongtoa(entry->stats.st_size);

	if (size == NULL)
	{
		stream_cat(env->stream, "? ");
		return;
	}

	stream_cat(env->stream, size);
	free(size);
	stream_cat(env->stream, " ");
}

//"Thu Dec  2 17:03:03 2021"

//"Dec  1  2020"
//"Dec 26 07:49"

#define SIX_MOUNTH_IN_SECONDS (6 * 30 * 24 * 60 * 60)
static void print_time(entry_t *entry, environment_t *env)
{
	time_t now = time(NULL);
	char *time_str = ctime(&entry->stats.st_mtime);


	stream_add_char(env->stream, '\t');
	stream_add_char(env->stream, time_str[4]);
	stream_add_char(env->stream, time_str[5]);
	stream_add_char(env->stream, time_str[6]);
	stream_add_char(env->stream, ' ');
	stream_add_char(env->stream, time_str[8]);
	stream_add_char(env->stream, time_str[9]);
	stream_add_char(env->stream, ' ');

	if (entry->stats.st_mtime > (now - SIX_MOUNTH_IN_SECONDS) && entry->stats.st_mtime < (now + SIX_MOUNTH_IN_SECONDS))
	{
		///printf("%s, print hour now %ld file: %ld\n", entry->filename, now, entry->stats.st_mtime);
		stream_add_char(env->stream, time_str[11]);
		stream_add_char(env->stream, time_str[12]);
		stream_add_char(env->stream, time_str[13]);
		stream_add_char(env->stream, time_str[14]);
		stream_add_char(env->stream, time_str[15]);
	}
	else
	{
		//printf("%s, print year year now %ld file: %ld\n", entry->filename, now, entry->stats.st_mtime);
		stream_add_char(env->stream, ' ');
		stream_add_char(env->stream, time_str[20]);
		stream_add_char(env->stream, time_str[21]);
		stream_add_char(env->stream, time_str[22]);
		stream_add_char(env->stream, time_str[23]);
	}
	if (strcmp(entry->filename, "testtest") == 0)
	{
		//printf("now %ld file: %ld", now, entry->stats.st_mtime);
	}
}

void links_handle(entry_t *entry, environment_t *env)
{
	char link_target[1024] = {0};
	if (!S_ISLNK(entry->stats.st_mode))
		return;

	ssize_t len = readlink(entry->full_path, link_target, sizeof(link_target) - 1);
	if (len != -1)
	{
		link_target[len] = '\0';
		stream_cat(env->stream, " -> ");
		stream_out_filename(env->stream, link_target);
	}
}

void print_long_format_line(entry_t *entry, environment_t *env)
{
	char permissions_str[11] = {0};

	struct passwd *passwd = getpwuid(entry->stats.st_uid);
	struct group *group = getgrgid(entry->stats.st_gid);

	set_permissions_str(permissions_str, entry->stats.st_mode);

	stream_cat(env->stream, permissions_str);
	stream_cat(env->stream, " ");

	print_nlinks(entry, env);

	if (passwd == NULL)
		stream_cat(env->stream, "?");
	else
		stream_cat(env->stream, passwd->pw_name);

	stream_cat(env->stream, " ");
	if (group == NULL)
		stream_cat(env->stream, "?");
	else
		stream_cat(env->stream, group->gr_name);
	stream_cat(env->stream, " ");

	print_size(entry, env);

	stream_cat(env->stream, " ");
	print_time(entry, env);
	stream_cat(env->stream, " ");

	stream_cat(env->stream, entry->printable_filename);
	//stream_cat(env->stream, entry_normal_suffix_char(entry, env));
	links_handle(entry, env);
	stream_cat_end_of_line(env->stream, "");
}

void print_entries_list(entry_list_t *entries, environment_t *env)
{
	entry_t *one_entry = entries->first;

	if (IS_FLAG_SET(env->flags, L_LLO))
	{
		char *size = ft_ulongtoa(entries->directory_size / 2);
		if (size != NULL)
		{
			stream_cat(env->stream, "total ");
			stream_cat_end_of_line(env->stream, size);
			free(size);
		}
	}

	while (one_entry != NULL)
	{
		if (IS_FLAG_SET(env->flags, L_LLO))
			print_long_format_line(one_entry, env);
		else
			print_normal_format_line(one_entry, env);

		one_entry = one_entry->next;
	}
	// stream_cat_end_of_line(env->stream, "");
}
