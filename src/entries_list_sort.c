#include <assert.h>

#include "entries_list_sort.h"
#include "libft.h"

bool entries_swap(entry_t *entry_a, entry_t *entry_b)
{
	assert(entry_a != NULL);
	assert(entry_b != NULL);

	if (entry_a == entry_b)
		return true;

	char *tmp_full_path = entry_a->full_path;
	char *tmp_filename = entry_a->filename;
	char *tmp_printable_filename = entry_a->printable_filename;
	struct stat tmp_stats = entry_a->stats;

	entry_a->filename = entry_b->filename;
	entry_a->printable_filename = entry_b->printable_filename;
	entry_a->full_path = entry_b->full_path;
	entry_a->stats = entry_b->stats;

	entry_b->filename = tmp_filename;
	entry_b->printable_filename = tmp_printable_filename;
	entry_b->full_path = tmp_full_path;
	entry_b->stats = tmp_stats;

	return true;
}

entry_t *entries_partition(entry_t *low, entry_t *high, cmp_func_t cmp)
{
	assert(low != NULL && high != NULL && cmp != NULL);

	entry_t *pivot = high;				  // Pivot is the last element in the range
	entry_t *partition_point = low->prev; // Tracks the last smaller element in the partition
	entry_t *current = low;

	// Traverse the list from `low` to `high - 1`
	while (current != high)
	{
		// If the current element is less than or equal to the pivot
		if (cmp(current, pivot) <= 0)
		{
			// Move the `last_smaller` pointer forward
			if (partition_point == NULL)
				partition_point = low;
			else
				partition_point = partition_point->next;

			// Swap the current element with the element at `last_smaller`
			entries_swap(partition_point, current);
		}

		current = current->next;
	}

	// Place the pivot element in its correct position
	if (partition_point == NULL)
		partition_point = low;
	else
		partition_point = partition_point->next;

	entries_swap(partition_point, high);

	// Return the new position of the pivot
	return partition_point;
}

bool entries_list_qsort(entry_t *low, entry_t *high, cmp_func_t cmp)
{
	assert(cmp != NULL);

	if (low && high && low != high && low != high->next)
	{
		entry_t *pivot = entries_partition(low, high, cmp);

		if (!entries_list_qsort(low, pivot->prev, cmp))
			return false;
		if (!entries_list_qsort(pivot->next, high, cmp))
			return false;
	}

	return true;
}

int compare_by_name(entry_t *entry_a, entry_t *entry_b)
{
	assert(entry_a != NULL);
	assert(entry_b != NULL);

	return ft_strcmp(entry_a->filename, entry_b->filename);
}

int compare_by_time(entry_t *entry_a, entry_t *entry_b)
{
	assert(entry_a != NULL);
	assert(entry_b != NULL);

	if (entry_a->stats.st_mtime > entry_b->stats.st_mtime)
		return -1;
	else if (entry_a->stats.st_mtime < entry_b->stats.st_mtime)
		return 1;
	
	/* if the time is the same, we compare by name ;) */
	return compare_by_name(entry_a, entry_b);
}

/*

static const char *skip_heading_punctuation(const char *filename)
{
	while (*filename && (*filename == '.' || ft_ispunct(*filename)))
		filename++;

	return filename;
}


int compare_by_name(entry_t *entry_a, entry_t *entry_b)
{
	assert(entry_a != NULL);
	assert(entry_b != NULL);


	if ( ft_strcmp(entry_a->filename, ".") == 0 && strcmp(entry_b->filename, "..") == 0 )
		return -1;

	if ( ft_strcmp(entry_b->filename, ".") == 0 && strcmp(entry_a->filename, "..") == 0 )
		return 1;

	if ( ft_strcmp(entry_a->filename, ".") == 0 || strcmp(entry_a->filename, "..") == 0 )
		return -1;

	if ( ft_strcmp(entry_b->filename, ".") == 0 || strcmp(entry_b->filename, "..") == 0 )
		return 1;

	const char *parsable_entry_a_filename = skip_heading_punctuation(entry_a->filename);
	const char *parsable_entry_b_filename = skip_heading_punctuation(entry_b->filename);

	return strcmp(parsable_entry_a_filename, parsable_entry_b_filename);

}

*/
