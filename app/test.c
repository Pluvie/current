int main (
    int argc,
    char** argv
)
{
  //test_arena();
  //test_map();
  map_correct_key_size();
  map_correct_value_size();
  map_default_flags();
  map_provided_flags();
  map_alloc_default_capacity();
  map_alloc_provided_capacity();
  map_alloc_provided_capacity_no_pow_2();
  map_alloc_provided_capacity_inferior_to_minimum();
  map_set_correct_key_value();
  map_set_overwrite_value();
  map_set_copy_key();
  map_set_avoid_copying_key_if_present();
  map_set_reuse_value_copy_if_key_present();
  map_set_copy_value();
  return 0;
}
