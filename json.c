#include <json-c/json.h>
#include <assert.h>

#include "json.h"

#define JSON_OBJECTS_BUFFER 100

static json_object** json_objects = NULL;
static int json_object_count = 0;
static int json_objects_size = JSON_OBJECTS_BUFFER;

void insert_json_object(json_object* object)
{
  assert(object != NULL);
  if (!json_objects)
    json_objects = (json_object**)malloc(JSON_OBJECTS_BUFFER * sizeof(json_object*));
  else if (json_object_count + 1 >= JSON_OBJECTS_BUFFER)
  {
    json_objects_size += JSON_OBJECTS_BUFFER;
    json_objects = (json_object**)realloc(json_objects, json_objects_size * sizeof(json_object*));
  }

  json_objects[json_object_count++] = object;
}

void delete_json_objects()
{
  if (json_object_count <= 0)
    return;

  int i;

  for (i = 0; i < json_object_count; ++i)
  {
    json_object_get(json_objects[i]); // Prevent put error
    json_object_put(json_objects[i]);
  }

  free(json_objects);
  json_objects = (json_object**)malloc(JSON_OBJECTS_BUFFER * sizeof(json_object*));
  json_object_count = 0;
}
