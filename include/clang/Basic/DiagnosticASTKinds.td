//==--- DiagnosticASTKinds.td - libast diagnostics ------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

let Component = "AST" in {

// Constant expression diagnostics. These (and their users) belong in Sema.
def note_expr_divide_by_zero : Note<"division by zero">;
def note_constexpr_invalid_cast : Note<
  "%select{reinterpret_cast|dynamic_cast|cast that performs the conversions of"
  " a reinterpret_cast|cast from %1}0 is not allowed in a constant expression">;
def note_constexpr_invalid_downcast : Note<
  "cannot cast object of dynamic type %0 to type %1">;
def note_constexpr_overflow : Note<
  "value %0 is outside the range of representable values of type %1">;
def note_constexpr_negative_shift : Note<"negative shift count %0">;
def note_constexpr_large_shift : Note<
  "shift count %0 >= width of type %1 (%2 bit%s2)">;
def note_constexpr_lshift_of_negative : Note<"left shift of negative value %0">;
def note_constexpr_lshift_discards : Note<"signed left shift discards bits">;
def note_constexpr_invalid_function : Note<
  "%select{non-constexpr|undefined}0 %select{function|constructor}1 %2 cannot "
  "be used in a constant expression">;
def note_constexpr_no_return : Note<
  "control reached end of constexpr function">;
def note_constexpr_virtual_call : Note<
  "cannot evaluate virtual function call in a constant expression">;
def note_constexpr_virtual_base : Note<
  "cannot construct object of type %0 with virtual base class "
  "in a constant expression">;
def note_constexpr_nonliteral : Note<
  "non-literal type %0 cannot be used in a constant expression">;
def note_constexpr_non_global : Note<
  "%select{pointer|reference}0 to %select{|subobject of }1"
  "%select{temporary|%3}2 is not a constant expression">;
def note_constexpr_array_index : Note<"cannot refer to element %0 of "
  "%select{array of %2 elements|non-array object}1 in a constant expression">;
def note_constexpr_float_arithmetic : Note<
  "floating point arithmetic produces %select{an infinity|a NaN}0">;
def note_constexpr_pointer_subtraction_not_same_array : Note<
  "subtracted pointers are not elements of the same array">;
def note_constexpr_pointer_comparison_base_classes : Note<
  "comparison of addresses of subobjects of different base classes "
  "has unspecified value">;
def note_constexpr_pointer_comparison_base_field : Note<
  "comparison of address of base class subobject %0 of class %1 to field %2 "
  "has unspecified value">;
def note_constexpr_pointer_comparison_differing_access : Note<
  "comparison of address of fields %0 and %2 of %4 with differing access "
  "specifiers (%1 vs %3) has unspecified value">;
def note_constexpr_compare_virtual_mem_ptr : Note<
  "comparison of pointer to virtual member function %0 has unspecified value">;
def note_constexpr_past_end : Note<
  "dereferenced pointer past the end of %select{|subobject of }0"
  "%select{temporary|%2}1 is not a constant expression">;
def note_constexpr_past_end_subobject : Note<
  "cannot %select{access base class of|access derived class of|access field of|"
  "access array element of|ERROR|call member function on|"
  "access real component of|access imaginary component of}0 "
  "pointer past the end of object">;
def note_constexpr_null_subobject : Note<
  "cannot %select{access base class of|access derived class of|access field of|"
  "access array element of|perform pointer arithmetic on|"
  "call member function on|access real component of|"
  "access imaginary component of}0 null pointer">;
def note_constexpr_var_init_non_constant : Note<
  "initializer of %0 is not a constant expression">;
def note_constexpr_typeid_polymorphic : Note<
  "typeid applied to expression of polymorphic type %0 is "
  "not allowed in a constant expression">;
def note_constexpr_void_comparison : Note<
  "comparison between unequal pointers to void has unspecified result">;
def note_constexpr_temporary_here : Note<"temporary created here">;
def note_constexpr_conditional_never_const : Note<
  "both arms of conditional operator are unable to produce a "
  "constant expression">;
def note_constexpr_depth_limit_exceeded : Note<
  "constexpr evaluation exceeded maximum depth of %0 calls">;
def note_constexpr_call_limit_exceeded : Note<
  "constexpr evaluation hit maximum call limit">;
def note_constexpr_step_limit_exceeded : Note<
  "constexpr evaluation hit maximum step limit; possible infinite loop?">;
def note_constexpr_lifetime_ended : Note<
  "%select{read of|assignment to|increment of|decrement of}0 "
  "%select{temporary|variable}1 whose lifetime has ended">;
def note_constexpr_access_uninit : Note<
  "%select{read of|assignment to|increment of|decrement of}0 "
  "object outside its lifetime is not allowed in a constant expression">;
def note_constexpr_modify_const_type : Note<
  "modification of object of const-qualified type %0 is not allowed "
  "in a constant expression">;
def note_constexpr_access_volatile_type : Note<
  "%select{read of|assignment to|increment of|decrement of}0 "
  "volatile-qualified type %1 is not allowed in a constant expression">;
def note_constexpr_access_volatile_obj : Note<
  "%select{read of|assignment to|increment of|decrement of}0 volatile "
  "%select{temporary|object %2|member %2}1 is not allowed in "
  "a constant expression">;
def note_constexpr_ltor_mutable : Note<
  "read of mutable member %0 is not allowed in a constant expression">;
def note_constexpr_ltor_non_const_int : Note<
  "read of non-const variable %0 is not allowed in a constant expression">;
def note_constexpr_ltor_non_constexpr : Note<
  "read of non-constexpr variable %0 is not allowed in a constant expression">;
def note_constexpr_access_null : Note<
  "%select{read of|assignment to|increment of|decrement of}0 "
  "dereferenced null pointer is not allowed in a constant expression">;
def note_constexpr_access_past_end : Note<
  "%select{read of|assignment to|increment of|decrement of}0 "
  "dereferenced one-past-the-end pointer is not allowed in a constant expression">;
def note_constexpr_access_inactive_union_member : Note<
  "%select{read of|assignment to|increment of|decrement of}0 "
  "member %1 of union with %select{active member %3|no active member}2 "
  "is not allowed in a constant expression">;
def note_constexpr_access_static_temporary : Note<
  "%select{read of|assignment to|increment of|decrement of}0 temporary "
  "is not allowed in a constant expression outside the expression that "
  "created the temporary">;
def note_constexpr_modify_global : Note<
  "a constant expression cannot modify an object that is visible outside "
  "that expression">;
def note_constexpr_calls_suppressed : Note<
  "(skipping %0 call%s0 in backtrace; use -fconstexpr-backtrace-limit=0 to "
  "see all)">;
def note_constexpr_call_here : Note<"in call to '%0'">;
def warn_integer_constant_overflow : Warning<
  "overflow in expression; result is %0 with type %1">,
  InGroup<DiagGroup<"integer-overflow">>;

// inline asm related.
let CategoryName = "Inline Assembly Issue" in {
  def err_asm_invalid_escape : Error<
    "invalid %% escape in inline assembly string">;
  def err_asm_unknown_symbolic_operand_name : Error<
    "unknown symbolic operand name in inline assembly string">;

  def err_asm_unterminated_symbolic_operand_name : Error<
    "unterminated symbolic operand name in inline assembly string">;
  def err_asm_empty_symbolic_operand_name : Error<
    "empty symbolic operand name in inline assembly string">;
  def err_asm_invalid_operand_number : Error<
    "invalid operand number in inline asm string">;
}


// Importing ASTs
def err_odr_variable_type_inconsistent : Error<
  "external variable %0 declared with incompatible types in different "
  "translation units (%1 vs. %2)">;
def err_odr_variable_multiple_def : Error<
  "external variable %0 defined in multiple translation units">;
def note_odr_value_here : Note<"declared here with type %0">;
def note_odr_defined_here : Note<"also defined here">;
def err_odr_function_type_inconsistent : Error<
  "external function %0 declared with incompatible types in different "
  "translation units (%1 vs. %2)">;
def warn_odr_tag_type_inconsistent : Warning<
  "type %0 has incompatible definitions in different translation units">,
  InGroup<DiagGroup<"odr">>;
def note_odr_tag_kind_here: Note<
  "%0 is a %select{struct|interface|union|class|enum}1 here">;
def note_odr_field : Note<"field %0 has type %1 here">;
def note_odr_missing_field : Note<"no corresponding field here">;
def note_odr_bit_field : Note<"bit-field %0 with type %1 and length %2 here">;
def note_odr_not_bit_field : Note<"field %0 is not a bit-field">;
def note_odr_base : Note<"class has base type %0">;
def note_odr_virtual_base : Note<
  "%select{non-virtual|virtual}0 derivation here">;
def note_odr_missing_base : Note<"no corresponding base class here">;
def note_odr_number_of_bases : Note<
  "class has %0 base %plural{1:class|:classes}0">;
def note_odr_enumerator : Note<"enumerator %0 with value %1 here">;
def note_odr_missing_enumerator : Note<"no corresponding enumerator here">;

def err_odr_field_type_inconsistent : Error<
  "field %0 declared with incompatible types in different "
  "translation units (%1 vs. %2)">;

// Importing Objective-C ASTs
def err_odr_ivar_type_inconsistent : Error<
  "instance variable %0 declared with incompatible types in different "
  "translation units (%1 vs. %2)">;
def err_odr_objc_superclass_inconsistent : Error<
  "class %0 has incompatible superclasses">;
def note_odr_objc_superclass : Note<"inherits from superclass %0 here">;
def note_odr_objc_missing_superclass : Note<"no corresponding superclass here">;
def err_odr_objc_method_result_type_inconsistent : Error<
  "%select{class|instance}0 method %1 has incompatible result types in "
  "different translation units (%2 vs. %3)">;
def err_odr_objc_method_num_params_inconsistent : Error<
  "%select{class|instance}0 method %1 has a different number of parameters in "
  "different translation units (%2 vs. %3)">;
def err_odr_objc_method_param_type_inconsistent : Error<
  "%select{class|instance}0 method %1 has a parameter with a different types "
  "in different translation units (%2 vs. %3)">;
def err_odr_objc_method_variadic_inconsistent : Error<
  "%select{class|instance}0 method %1 is variadic in one translation unit "
  "and not variadic in another">;
def note_odr_objc_method_here : Note<
  "%select{class|instance}0 method %1 also declared here">;
def err_odr_objc_property_type_inconsistent : Error<
  "property %0 declared with incompatible types in different "
  "translation units (%1 vs. %2)">;
def err_odr_objc_property_impl_kind_inconsistent : Error<
  "property %0 is implemented with %select{@synthesize|@dynamic}1 in one "
  "translation but %select{@dynamic|@synthesize}1 in another translation unit">;
def note_odr_objc_property_impl_kind : Note<
  "property %0 is implemented with %select{@synthesize|@dynamic}1 here">;
def err_odr_objc_synthesize_ivar_inconsistent : Error<
  "property %0 is synthesized to different ivars in different translation "
  "units (%1 vs. %2)">;
def note_odr_objc_synthesize_ivar_here : Note<
  "property is synthesized to ivar %0 here">;

// Importing C++ ASTs
def err_odr_different_num_template_parameters : Error<
  "template parameter lists have a different number of parameters (%0 vs %1)">;
def note_odr_template_parameter_list : Note<
  "template parameter list also declared here">;
def err_odr_different_template_parameter_kind : Error<
  "template parameter has different kinds in different translation units">;
def note_odr_template_parameter_here : Note<
  "template parameter declared here">;
def err_odr_parameter_pack_non_pack : Error<
  "parameter kind mismatch; parameter is %select{not a|a}0 parameter pack">;
def note_odr_parameter_pack_non_pack : Note<
  "%select{parameter|parameter pack}0 declared here">;
def err_odr_non_type_parameter_type_inconsistent : Error<
  "non-type template parameter declared with incompatible types in different "
  "translation units (%0 vs. %1)">;
def err_unsupported_ast_node: Error<"cannot import unsupported AST node %0">;
}
