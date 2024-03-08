test(set_init_provided_flags) {

  given("a set")
    struct set set = set_init(i32);
  
  when("flags are provided")
    set_flag_enable(&set, Set_Flag__Copy_Elements);
  
  calling("set_init()")
  
  must("create the set with the provided flags")
    verify(set.elements.flags & Map_Flag__Copy_Keys);
    verify(set.elements.flags & Map_Flag__Copy_Values);

  success()
    set_destroy(&set);
}
