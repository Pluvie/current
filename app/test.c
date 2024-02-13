int main (
    int argc,
    char** argv
)
{
  // arena tests here
  // arena_correct_init();

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
  map_set_rehash_trigger();
  map_set_rehash_avoid_double_copy();
  map_get_retrieve_value();
  map_get_return_null();
  map_del_remove_entry();
  map_del_do_nothing();
  map_has_true_if_key_present();
  map_has_false_if_key_not_present();

  return 0;
}
