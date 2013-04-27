#include "utils.h"

hash_map *make_hash_map()
{
	hash_map *ret = (hash_map *) malloc(sizeof(hash_map));
	return ret;
}

int hash(char *key)
{
	int h = 5381;

	unsigned char c;
	for (c = *key; c != '\0'; c = *++key)
		h = h * 33 + c;

	return h % 256;
}

void *get_hash(hash_map *m, char *key)
{
	list_node *cur = m->buckets[hash(key)];
	for (; cur->next != NULL; cur = cur->next) {
		if (cur->data != NULL) {
			if (strcmp(key, ((hash_val *) cur->data)->key) == 0) {
				return ((hash_val *) cur->data)->val;
			}
		}
	}
	return NULL;
}

void set_hash(hash_map *m, char *key, void *val)
{
	hash_val *hv = (hash_val *) malloc(sizeof(hash_val));
	hv->key = key;
	hv->val = val;
	int hk = hash(key);
	if (m->buckets[hk] == NULL) {
		m->buckets[hk] = make_list();
	}
	insert_list(m->buckets[hk], (void *) hv);
}

list_node *make_list_node(void *d)
{
	list_node *ret = (list_node *) malloc(sizeof(list_node));
	ret->data = d;
	return ret;
}

list_node *make_list()
{
	list_node *start = (list_node *) malloc(sizeof(list_node));
	list_node *end = (list_node *) malloc(sizeof(list_node));
	start->prev = NULL;
	start->next = end;
	start->data = NULL;
	end->prev = start;
	end->next = NULL;
	end->data = NULL;
	return start;
}

int find_list(list_node *l, void *data)
{
	list_node *c;
	for (c = l; c->next != NULL; c = c->next) {
		if (c->data == data) {
			return 1;
		}
	}
	return 0;
}

void insert_list(list_node *l, void *data)
{
	list_node *ins = (list_node *) malloc(sizeof(list_node));
	ins->data = data;
	ins->next = l->next;
	l->next = ins;
	ins->next->prev = ins;
	ins->prev = l;
}

void remove_list(list_node *l, void *data)
{
	list_node *c;
	for (c = l; c->next != NULL; c = c->next) {
		if (c->data == data) {
			c->prev->next = c->next;
			c->next->prev = c->prev;
		}
	}
}