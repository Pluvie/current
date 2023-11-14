/**
               ___      .______       _______ .__   __.      ___      
              /   \     |   _  \     |   ____||  \ |  |     /   \     
             /  ^  \    |  |_)  |    |  |__   |   \|  |    /  ^  \    
            /  /_\  \   |      /     |   __|  |  . `  |   /  /_\  \   
           /  _____  \  |  |\  \----.|  |____ |  |\   |  /  _____  \  
          /__/     \__\ | _| `._____||_______||__| \__| /__/     \__\ 
                                                                                      **/

typedef struct arena arena;
struct arena {
  byte*   data;
  int64   size;
  int64   pos;
  arena*  next;
};

function(arena_calloc, void*) (arena*, int64, int64);
function(arena_destroy, void) (arena*);
function(arena_init, arena*) (int64);
function(arena_malloc, void*) (arena*, int64);
function(arena_realloc, void*) (arena*, void*, int64);
