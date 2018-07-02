/****************************************************************************
 * Copyright 2018 Matthew Ballance
 *
 ****************************************************************************/
 
grammar systemverilog;

// A.1 Source text

// A.1.1. Library source text
library_text : 
  ( library_description )*
  EOF
  ;
  
library_description:
  library_declaration
  | include_statement
  | config_declaration
  | ';'
  ;
  
library_declaration:
  'library' library_identifier file_path_spec ( ',' file_path_spec )*
  ( '-incdir' file_path_spec ( ',' file_path_spec )* )? ';'
  ;
  
include_statement: 
  'include' file_path_spec ';'
  ;
 
// TODO: file_path_spec is system-dependent
file_path_spec: 
  identifier 
  ;

// A.1.2 SystemVerilog source text
source_text : 
  ( timeunits_declaration )? ( description )* EOF
  ;
  
description:
  module_declaration
//TODO:  | udp_declaration
  | interface_declaration
  | program_declaration
  | package_declaration
  | ( attribute_instance )* package_item
  | ( attribute_instance )* bind_directive
  | config_declaration
  ;
  
module_nonansi_header:
  ( attribute_instance )? module_keyword ( lifetime )? module_identifier
  ( package_import_declaration )* ( parameter_port_list )? list_of_ports ';'
  ;
  
module_ansi_header:
  ( attribute_instance )* module_keyword ( lifetime )? module_identifier
  ( package_import_declaration )* ( parameter_port_list )? ( list_of_port_declarations )? ';'
  ;
  
module_declaration:
  module_nonansi_header ( timeunits_declaration )? ( module_item )*
  'endmodule' ( ':' module_identifier )?
  | module_ansi_header ( timeunits_declaration )? ( non_port_module_item )*
  'endmodule' ( ':' module_identifier )?
  | ( attribute_instance )* module_keyword ( lifetime )? module_identifier '(' '.*' ')' ';'
    ( timeunits_declaration )? ( module_item )* 'endmodule' ( ':' module_identifier )?
  | 'extern' module_nonansi_header
  | 'extern' module_ansi_header
  ;
  
module_keyword: 
  'module' | 'macromodule'
  ;

interface_declaration:
  interface_nonansi_header ( timeunits_declaration )? ( interface_item )*
  'endinterface' ( ':' interface_identifier )?
  | interface_ansi_header ( timeunits_declaration )? ( non_port_interface_item )*
  'endinterface' ( ':' interface_identifier )?
  | ( attribute_instance )* 'interface' interface_identifier '(' '.*' ')' ';'
  ( timeunits_declaration )? ( interface_item )*
  'endinterface' ( ':' interface_identifier )?
  | 'extern' interface_nonansi_header
  | 'extern' interface_ansi_header
  ;
  
interface_nonansi_header:
  ( attribute_instance )* 'interface' ( lifetime )? interface_identifier
  ( package_import_declaration )* ( parameter_port_list )? list_of_ports ';'
  ;
  
interface_ansi_header:
  (attribute_instance )* 'interface' ( lifetime )? interface_identifier
  ( package_import_declaration )*
  ( parameter_port_list )? ( list_of_port_declarations )? ';'
  ;
  
program_declaration:
  program_nonansi_header ( timeunits_declaration )? ( program_item )*
  'endprogram' ( ':' program_identifier )?
  | program_ansi_header ( timeunits_declaration )? ( non_port_program_item )*
  'endprogram' ( ':' program_identifier )?
  | ( attribute_instance )* 'program' program_identifier '(' '.*' ')' ';'
  ( timeunits_declaration )? ( program_item )*
  'endprogram' ( ':' program_identifier )?
  | 'extern' program_nonansi_header
  | 'extern' program_ansi_header
  ;
  
program_nonansi_header:
  ( attribute_instance )* 'program' ( lifetime )? program_identifier
  ( package_import_declaration )* ( parameter_port_list )? list_of_ports ';'
  ;
program_ansi_header:
  (attribute_instance )* 'program' ( lifetime )? program_identifier 
  ( package_import_declaration )* ( parameter_port_list )? ( list_of_port_declarations )? ';'
  ;
  
checker_declaration:
  'checker' checker_identifier ( '(' ( checker_port_list )? ')' )? ';'
  ( ( attribute_instance )* checker_or_generate_item )*
  'endchecker' ( ':' checker_identifier )?
  ;
  
class_declaration:
  ( 'virtual' )? 'class' ( lifetime )? class_identifier ( parameter_port_list )?
  ( 'extends' class_type ( '(' list_of_arguments ')' )? )?
  ( 'implements' interface_class_type ( ',' interface_class_type )* )? ';'
  ( class_item )*
  'endclass' ( ':' class_identifier )?
  ;
  
interface_class_type: 
  ps_class_identifier ( parameter_value_assignment )?
  ;
  
interface_class_declaration:
  'interface' 'class' class_identifier ( parameter_port_list )?
  ( 'extends' interface_class_type ( ',' interface_class_type )* )? ';'
  ( interface_class_item )*
  'endclass' ( ':' class_identifier )?
  ;
  
interface_class_item:
  type_declaration
  | ( attribute_instance )* interface_class_method
  | local_parameter_declaration ';'
  | parameter_declaration ';'
  | ';'
  ;
  
interface_class_method:
  'pure' 'virtual' method_prototype ';'
  ;
  
package_declaration:
  ( attribute_instance )* 'package' ( lifetime )? package_identifier ';'
  ( timeunits_declaration )? ( ( attribute_instance )* package_item )*
  'endpackage' ( ':' package_identifier )?
  ;
  
timeunits_declaration:
  'timeunit' time_literal ( '/' time_literal )? ';'
  | 'timeprecision' time_literal ';'
  | 'timeunit' time_literal ';' 'timeprecision' time_literal ';'
  | 'timeprecision' time_literal ';' 'timeunit' time_literal ';'
  ;

//***********************************************************************
//* A.1.3 Module parameters and ports
//***********************************************************************
parameter_port_list:
  '#' '(' list_of_param_assignments ( ',' parameter_port_declaration )* ')'
  | '#' '(' parameter_port_declaration ( ',' parameter_port_declaration )* ')'
  | '#' '(' ')'
  ;
  
parameter_port_declaration:
  parameter_declaration
  | local_parameter_declaration
  | data_type list_of_param_assignments
  | 'type' list_of_type_assignments
  ;
  
list_of_ports: 
  '(' port ( ',' port )* ')'
  ;
  
list_of_port_declarations:
  '(' ( ( attribute_instance)* ansi_port_declaration ( ',' ( attribute_instance)* ansi_port_declaration )* )? ')'
  ;

port_declaration:
  ( attribute_instance )* inout_declaration
  | ( attribute_instance )* input_declaration
  | ( attribute_instance )* output_declaration
  | ( attribute_instance )* ref_declaration
  | ( attribute_instance )* interface_port_declaration
  ;
  
port:
  ( port_expression )?
  | '.' port_identifier '(' ( port_expression )? ')'
  ;
  
port_expression:
  port_reference
  | '{' port_reference ( ',' port_reference )* '}'
  ;
  
port_reference:
  port_identifier constant_select
  ;
  
port_direction:
  'input' 
  | 'output' 
  | 'inout' 
  | 'ref'
  ;
  
net_port_header: 
  ( port_direction )? net_port_type
  ;
  
variable_port_header: 
  ( port_direction )? variable_port_type
  ;
  
interface_port_header:
  interface_identifier ( '.' modport_identifier )?
  | 'interface' ( '.' modport_identifier )?
  ;
  
ansi_port_declaration:
  ( net_port_header | interface_port_header )? port_identifier ( unpacked_dimension )*
    ( '=' constant_expression )?
  | ( variable_port_header )? port_identifier ( variable_dimension )* ( '=' constant_expression )?
  | ( port_direction )? '.' port_identifier '(' ( expression )? ')'
  ;

//***********************************************************************
//* A.1.4 Module items
//***********************************************************************

elaboration_system_task:
  '$fatal' ( '(' finish_number (',' list_of_arguments )? ')' )? ';'
  | '$error' ( '(' ( list_of_arguments )? ')' )? ';'
  | '$warning' ( '(' ( list_of_arguments )? ')' )? ';'
  | '$info' ( '(' ( list_of_arguments )? ')' )? ';'
  ;
  
finish_number: 
  '0' | '1' | '2'
  ;
  
module_common_item:
  module_or_generate_item_declaration
  | interface_instantiation
  | program_instantiation
  | assertion_item
  | bind_directive
  | continuous_assign
  | net_alias
  | initial_construct
  | final_construct
  | always_construct
  | loop_generate_construct
  | conditional_generate_construct
  | elaboration_system_task
  ;
  
module_item:
  port_declaration ';'
  | non_port_module_item
  ;
  
module_or_generate_item:
  ( attribute_instance )* parameter_override
  | ( attribute_instance )* gate_instantiation
  | ( attribute_instance )* udp_instantiation
  | ( attribute_instance )* module_instantiation
  | ( attribute_instance )* module_common_item
  ;
  
module_or_generate_item_declaration:
  package_or_generate_item_declaration
  | genvar_declaration
  | clocking_declaration
  | 'default' 'clocking' clocking_identifier ';'
  | 'default' 'disable' 'iff' expression_or_dist ';'
  ;
  
non_port_module_item:
  generate_region
  | module_or_generate_item
  | specify_block
  | ( attribute_instance )* specparam_declaration
  | program_declaration
  | module_declaration
  | interface_declaration
  | timeunits_declaration
  ;
  
parameter_override: 
  'defparam' list_of_defparam_assignments ';'
  ;
  
bind_directive:
  'bind' bind_target_scope (':' bind_target_instance_list)? bind_instantiation ';'
  | 'bind' bind_target_instance bind_instantiation ';'
  ;
  
bind_target_scope:
  module_identifier
  | interface_identifier
  ;
  
bind_target_instance:
  hierarchical_identifier constant_bit_select
  ;
  
bind_target_instance_list:
  bind_target_instance ( ',' bind_target_instance )*
  ;
  
bind_instantiation:
  program_instantiation
  | module_instantiation
  | interface_instantiation
  | checker_instantiation 
  ;

//***********************************************************************
//* A.1.5 Configuration source text
//***********************************************************************
config_declaration:
  'config' config_identifier ';'
  ( local_parameter_declaration ';' )*
  design_statement
  ( config_rule_statement )*
  'endconfig' ( ':' config_identifier )?
  ;
  
design_statement: 
  'design' ( ( library_identifier '.' )? cell_identifier )* ';'
  ;
  
config_rule_statement:
  default_clause liblist_clause ';'
  | inst_clause liblist_clause ';'
  | inst_clause use_clause ';'
  | cell_clause liblist_clause ';'
  | cell_clause use_clause ';'
  ;
  
default_clause: 
  'default'
  ;

inst_clause: 
  'instance' inst_name
  ;
  
inst_name: 
  topmodule_identifier ( '.' instance_identifier )*
  ;
  
cell_clause: 
  'cell' ( library_identifier '.' )? cell_identifier
  ;
  
liblist_clause: 
  'liblist' (library_identifier)*
  ;
  
use_clause: 
  'use' ( library_identifier '.' )? cell_identifier ( ':' 'config' )?
  | 'use' named_parameter_assignment ( ',' named_parameter_assignment )* ( ':' 'config' )?
  | 'use' ( library_identifier '.' )? cell_identifier named_parameter_assignment
  ( ',' named_parameter_assignment )* ( ':' 'config' )?
  ;
  
//***********************************************************************
//* A.1.6 Interface items
//***********************************************************************
interface_or_generate_item:
  ( attribute_instance )* module_common_item
  | ( attribute_instance )* modport_declaration
  | ( attribute_instance )* extern_tf_declaration
  ;
  
extern_tf_declaration:
  'extern' method_prototype ';'
  | 'extern' 'forkjoin' task_prototype ';'
  ;
  
interface_item:
  port_declaration ';'
  | non_port_interface_item
  ;
  
non_port_interface_item:
  generate_region
  | interface_or_generate_item
  | program_declaration
  | interface_declaration
  | timeunits_declaration
  ;
  
//***********************************************************************
//* A.1.7 Program items
//***********************************************************************
program_item:
  port_declaration ';'
  | non_port_program_item
  ;
  
non_port_program_item:
  ( attribute_instance )* continuous_assign
  | ( attribute_instance )* module_or_generate_item_declaration
  | ( attribute_instance )* initial_construct
  | ( attribute_instance )* final_construct
  | ( attribute_instance )* concurrent_assertion_item
  | timeunits_declaration
  | program_generate_item
  ;
  
program_generate_item:
  loop_generate_construct
  | conditional_generate_construct  
  | generate_region
  | elaboration_system_task
  ;
  
//***********************************************************************
//* A.1.8 Checker items
//***********************************************************************
checker_port_list:
  checker_port_item (',' checker_port_item)*
  ;
  
checker_port_item:
  ( attribute_instance )* ( checker_port_direction )? property_formal_type formal_port_identifier
    (variable_dimension)* ( '=' property_actual_arg )?
  ;
  
checker_port_direction:
  'input' | 'output'
  ;
  
checker_or_generate_item:
  checker_or_generate_item_declaration
  | initial_construct
  | always_construct
  | final_construct
  | assertion_item
  | continuous_assign
  | checker_generate_item
  ;
  
checker_or_generate_item_declaration:
  ( 'rand' )? data_declaration
  | function_declaration
  | checker_declaration
  | assertion_item_declaration
  | covergroup_declaration
  | overload_declaration
  | genvar_declaration
  | clocking_declaration
  | 'default' 'clocking' clocking_identifier ';'
  | 'default' 'disable' 'iff' expression_or_dist ';'
  | ';'
  ;
  
checker_generate_item:
  loop_generate_construct
  | conditional_generate_construct
  | generate_region
  | elaboration_system_task
  ;

//***********************************************************************
//* A.1.9 Class items
//***********************************************************************
class_item:
  ( attribute_instance )* class_property
  | ( attribute_instance )* class_method
  | ( attribute_instance )* class_constraint
  | ( attribute_instance )* class_declaration
  | ( attribute_instance )* covergroup_declaration
  | local_parameter_declaration ';'
  | parameter_declaration ';'
  | ';'
  ;
  
class_property:
  ( property_qualifier )* data_declaration
  | 'const' ( class_item_qualifier )* data_type const_identifier ( '=' constant_expression )? ';'
  ;
  
class_method:
  ( method_qualifier )* task_declaration
  | ( method_qualifier )* function_declaration
  | 'pure' 'virtual' ( class_item_qualifier )* method_prototype ';'
  | 'extern' ( method_qualifier )* method_prototype ';'
  | ( method_qualifier )* class_constructor_declaration
  | 'extern' ( method_qualifier )* class_constructor_prototype
  ;
  
class_constructor_prototype:
  'function' 'new' ( '(' ( tf_port_list )? ')' )? ';'
  ;
  
class_constraint:
  constraint_prototype
  | constraint_declaration
  ;
  
class_item_qualifier:
  'static'
  | 'protected'
  | 'local'
  ;
  
property_qualifier:
  random_qualifier
  | class_item_qualifier
  ;
  
random_qualifier:
  'rand'
  | 'randc'
  ;
  
method_qualifier:
  ( 'pure' )? 'virtual'
  | class_item_qualifier
  ;
  
method_prototype:
  task_prototype
  | function_prototype
  ;
  
class_constructor_declaration:
  'function' ( class_scope )? 'new' ( '(' ( tf_port_list )? ')' )? ';'
  ( block_item_declaration )*
  ( 'super' '.' 'new' ( '(' list_of_arguments ')' )? ';' )?
  ( function_statement_or_null )*
  'endfunction' ( ':' 'new' )? 
  ;

//***********************************************************************
//* A.1.10 Constraints
//***********************************************************************
constraint_declaration: 
  ( 'static' )? 'constraint' constraint_identifier constraint_block
  ;
  
constraint_block: 
  '{' ( constraint_block_item )* '}'
  ;
  
constraint_block_item:
  'solve' solve_before_list 'before' solve_before_list ';'
  | constraint_expression
  ;
  
solve_before_list: 
  constraint_primary ( ',' constraint_primary )*
  ;
  
constraint_primary: 
  ( implicit_class_handle '.' | class_scope )? hierarchical_identifier select
  ;
  
constraint_expression:
  ( 'soft' )? expression_or_dist ';'
  | uniqueness_constraint ';'
  | expression '->' constraint_set
  | 'if' '(' expression ')' constraint_set ( 'else' constraint_set )?
  | 'foreach' '(' ps_or_hierarchical_array_identifier ( loop_variables )? ')' constraint_set
  | 'disable' 'soft' constraint_primary ';'
  ;
  
uniqueness_constraint:
  'unique' '{' open_range_list '}'
  ;
  
constraint_set:
  constraint_expression
  | '{' ( constraint_expression )* '}'
  ;
  
dist_list: 
  dist_item ( ',' dist_item )*
  ;
  
dist_item: 
  value_range ( dist_weight )?
  ;
  
dist_weight:
  ':=' expression
  | ':/' expression
  ;
  
constraint_prototype: 
  (constraint_prototype_qualifier)? ( 'static' )? constraint constraint_identifier ';'
  ;
  
constraint_prototype_qualifier: 
  'extern' | 'pure'
  ;
  
extern_constraint_declaration:
  ( 'static' )? 'constraint' class_scope constraint_identifier constraint_block
  ;
  
identifier_list: 
  identifier ( ',' identifier )* 
  ;
  
//***********************************************************************
//* A.1.11 Package items
//***********************************************************************
package_item:
  package_or_generate_item_declaration
  | anonymous_program
  | package_export_declaration
  | timeunits_declaration
  ;
  
package_or_generate_item_declaration:
  net_declaration
  | data_declaration
  | task_declaration
  | function_declaration
  | checker_declaration
  | dpi_import_export
  | extern_constraint_declaration
  | class_declaration
  | class_constructor_declaration
  | local_parameter_declaration ';'
  | parameter_declaration ';'
  | covergroup_declaration
  | overload_declaration
  | assertion_item_declaration
  | ';'
  ;
  
anonymous_program: 
  'program' ';' ( anonymous_program_item )* 'endprogram'
  ;
  
anonymous_program_item:
  task_declaration
  | function_declaration
  | class_declaration
  | covergroup_declaration
  | class_constructor_declaration
  | ';'
  ;

//***************************************************************************
//* A.2 Declarations
//***************************************************************************

//***********************************************************************
//* A.2.1 Declaration types
//***********************************************************************

//*******************************************************************
//* A.2.1.1 Module parameter declarations
//*******************************************************************
local_parameter_declaration:
  'localparam' data_type_or_implicit list_of_param_assignments
  | 'localparam type' list_of_type_assignments
  ;
  
parameter_declaration:
  'parameter' data_type_or_implicit list_of_param_assignments
  | 'parameter' 'type' list_of_type_assignments
  ;
  
specparam_declaration:
  'specparam' ( packed_dimension )? list_of_specparam_assignments ';'
  ;

//*******************************************************************
//* A.2.1.2 Port declarations
//*******************************************************************
inout_declaration:
  'inout' net_port_type list_of_port_identifiers
  ;
  
input_declaration:
  'input' net_port_type list_of_port_identifiers
  | 'input' variable_port_type list_of_variable_identifiers
  ;
  
output_declaration:
  'output' net_port_type list_of_port_identifiers
  | 'output' variable_port_type list_of_variable_port_identifiers
  ;
  
interface_port_declaration:
  interface_identifier list_of_interface_identifiers
  | interface_identifier '.' modport_identifier list_of_interface_identifiers
  ;
  
ref_declaration: 
  'ref' variable_port_type list_of_variable_identifiers 
  ;

//*******************************************************************
//* A.2.1.3 Type declarations
//*******************************************************************
data_declaration:
  ( 'const' )? ( 'var' )? ( lifetime )? data_type_or_implicit list_of_variable_decl_assignments ';'
  | type_declaration
  | package_import_declaration net_type_declaration
  ;
  
package_import_declaration:
  'import' package_import_item ( ',' package_import_item )* ';'
  ;
  
package_import_item:
  package_identifier '::' identifier
  | package_identifier '::' '*'
  ;
  
package_export_declaration:
  'export' '*' '::' '*' ';'
  | 'export' package_import_item ( ',' package_import_item )* ';'
  ;
  
genvar_declaration: 
  'genvar' list_of_genvar_identifiers ';'
  ;
  
net_declaration:
  net_type ( drive_strength | charge_strength )? ( 'vectored' | 'scalared' )?
  data_type_or_implicit ( delay3 )? list_of_net_decl_assignments ';'
  | net_type_identifier ( delay_control )? list_of_net_decl_assignments ';'
  | 'interconnect' implicit_data_type ( '#' delay_value )? net_identifier ( unpacked_dimension )*
    ( ',' net_identifier ( unpacked_dimension )*)? ';'
  ;
  
type_declaration:
  'typedef' data_type type_identifier (variable_dimension)* ';'
  | 'typedef' interface_instance_identifier constant_bit_select '.' type_identifier type_identifier ';'
  | typedef ( 'enum' | 'struct' | 'union' | 'class' | 'interface' 'class' )? type_identifier ';'
  ;
  
net_type_declaration:
  'nettype' data_type net_type_identifier
    ( 'with' ( package_scope | class_scope )? tf_identifier )? ';'
  | 'nettype' ( package_scope | class_scope )? net_type_identifier net_type_identifier ';'
  ;
  
lifetime: 
  'static' | 'automatic'
  ;
  
//***********************************************************************
//* A.2.2 Declaration data types
//***********************************************************************

//*******************************************************************
//* A.2.2.1 Net and variable types
//*******************************************************************
casting_type: 
  simple_type | constant_primary | signing | 'string' | 'const'
  ;
  
data_type:
  integer_vector_type ( signing )? ( packed_dimension )*
  | integer_atom_type ( signing )?
  | non_integer_type
  | struct_union ( 'packed' ( signing )? )? '{' struct_union_member ( struct_union_member )* '}' ( packed_dimension )*
  | 'enum' ( enum_base_type )? '{' enum_name_declaration ( ',' enum_name_declaration )* '}' ( packed_dimension )*
  | 'string'
  | 'chandle'
  | 'virtual' ( 'interface' )? interface_identifier ( parameter_value_assignment )? ( '.' modport_identifier )?
  | ( class_scope | package_scope )? type_identifier ( packed_dimension )*
  | class_type
  | 'event'
  | ps_covergroup_identifier
  | type_reference
  ;
  
data_type_or_implicit:
  data_type
  | implicit_data_type
  ;
  
implicit_data_type: 
  ( signing )? ( packed_dimension )*
  ;
  
enum_base_type:
  integer_atom_type ( signing )?
  | integer_vector_type ( signing )? ( packed_dimension )?
  | type_identifier ( packed_dimension )?
  ;
  
enum_name_declaration:
  enum_identifier ( '[' integral_number ( ':' integral_number )? ']' )? ( '=' constant_expression )?
  ;
  
class_scope: 
  class_type '::'
  ;
  
class_type:
  ps_class_identifier ( parameter_value_assignment )?
  ( '::' class_identifier ( parameter_value_assignment )? )*
  ;
  
integer_type: 
  integer_vector_type | integer_atom_type
  ;
  
integer_atom_type: 
  'byte' | 'shortint' | 'int' | 'longint' | 'integer' | 'time'
  ;
  
integer_vector_type: 
  'bit' | 'logic' | 'reg'
  ;

non_integer_type: 
  'shortreal' | 'real' | 'realtime'
  ;
  
net_type: 
  'supply0' | 'supply1' | 'tri' | 'triand' | 'trior' | 'trireg' | 'tri0' | 'tri1' | 'uwire' | 'wire' | 'wand' | 'wor'
  ;
  
net_port_type:
  ( net_type )? data_type_or_implicit
  | net_type_identifier
  | 'interconnect' implicit_data_type
  ;
  
variable_port_type: 
  var_data_type
  ;
  
var_data_type: 
  data_type 
  | 'var' data_type_or_implicit
  ;
  
signing: 
  'signed' | 'unsigned'
  ;
  
simple_type: 
  integer_type 
  | non_integer_type 
  | ps_type_identifier 
  | ps_parameter_identifier
  ;
  
struct_union_member:
  ( attribute_instance )* (random_qualifier)? data_type_or_void list_of_variable_decl_assignments ';'
  ;
  
data_type_or_void: 
  data_type 
  | 'void'
  ;
  
struct_union: 
  'struct' 
  | 'union' ( 'tagged' )?
  ;
  
type_reference:
  'type' '(' expression ')'
  | 'type' '(' data_type ')'
  ;
  
//*******************************************************************
//* A.2.2.2 Strengths
//*******************************************************************
drive_strength:
  '(' strength0 ',' strength1 ')'
  | '(' strength1 ',' strength0 ')'
  | '(' strength0 ',' highz1 ')'
  | '(' strength1 ',' highz0 ')'
  | '(' highz0 ',' strength1 ')'
  | '(' highz1 ',' strength0 ')'
  ;
  
strength0: 
  'supply0' 
  | 'strong0' 
  | 'pull0' 
  | 'weak0'
  ;
  
strength1: 
  'supply1' 
  | 'strong1' 
  | 'pull1' 
  | 'weak1'
  ;
  
charge_strength: 
  '(' 'small' ')' 
  | '(' 'medium' ')' 
  | '(' 'large' ')'
  ;

//*******************************************************************
//* A.2.2.3 Delays
//*******************************************************************
delay3: 
  '#' delay_value 
  | '#' '(' mintypmax_expression ( ',' mintypmax_expression ( ',' mintypmax_expression )? )? ')'
  ;
  
delay2: 
  '#' delay_value 
  | '#' '(' mintypmax_expression ( ',' mintypmax_expression )? ')'
  ;
  
delay_value:
  unsigned_number
  | real_number
  | ps_identifier
  | time_literal
  | '1step'
  ;

//***********************************************************************
//* A.2.3 Declaration lists
//***********************************************************************

list_of_defparam_assignments: 
  defparam_assignment ( ',' defparam_assignment )*
  ;
  
list_of_genvar_identifiers: 
  genvar_identifier ( ',' genvar_identifier )*
  ;
  
list_of_interface_identifiers: 
  interface_identifier ( unpacked_dimension )*
    ( ',' interface_identifier ( unpacked_dimension )* )*
  ;
  
list_of_net_decl_assignments: 
  net_decl_assignment ( ',' net_decl_assignment )*
  ;
  
list_of_param_assignments: 
  param_assignment ( ',' param_assignment )*
  ;
  
list_of_port_identifiers: 
  port_identifier ( unpacked_dimension )*
    ( ',' port_identifier ( unpacked_dimension )* )*
  ;
  
list_of_udp_port_identifiers: 
  port_identifier ( ',' port_identifier )*
  ;
  
list_of_specparam_assignments: 
  specparam_assignment ( ',' specparam_assignment )*
  ;
  
list_of_tf_variable_identifiers: 
  port_identifier ( variable_dimension )* ( '=' expression )?
  ( ',' port_identifier ( variable_dimension )* ( '=' expression )? )*
  ;
  
list_of_type_assignments: 
  type_assignment ( ',' type_assignment )*
  ;
  
list_of_variable_decl_assignments: 
  variable_decl_assignment ( ',' variable_decl_assignment )*
  ;
  
list_of_variable_identifiers: 
  variable_identifier ( variable_dimension )*
    ( ',' variable_identifier ( variable_dimension )* )*
  ;
  
list_of_variable_port_identifiers: 
  port_identifier ( variable_dimension )* ( '=' constant_expression )?
    ( ',' port_identifier ( variable_dimension )* ( '=' constant_expression )? )*
  ; 

//***********************************************************************
//* A.2.4 Declaration assignments
//***********************************************************************

defparam_assignment: 
  hierarchical_parameter_identifier '=' constant_mintypmax_expression
  ;
  
net_decl_assignment: 
  net_identifier ( unpacked_dimension )* ( '=' expression )?
  ;
  
param_assignment:
  parameter_identifier ( unpacked_dimension )* ( '=' constant_param_expression )?
  ;
  
specparam_assignment:
  specparam_identifier '=' constant_mintypmax_expression
  | pulse_control_specparam
  ;
  
type_assignment:
  type_identifier ( '=' data_type )?
  ;
  
pulse_control_specparam:
  'PATHPULSE$' '=' '(' reject_limit_value ( ',' error_limit_value )? ')'
  | 'PATHPULSE$' specify_input_terminal_descriptor '$' specify_output_terminal_descriptor
    '=' '(' reject_limit_value ( ',' error_limit_value )? ')'
  ;
  
error_limit_value: 
  limit_value
  ;
  
reject_limit_value: 
  limit_value
  ;
  
limit_value: 
  constant_mintypmax_expression
  ;
  
variable_decl_assignment:
  variable_identifier ( variable_dimension )* ( '=' expression )?
  | dynamic_array_variable_identifier unsized_dimension ( variable_dimension )*
    ( '=' dynamic_array_new )?
  | class_variable_identifier ( '=' class_new )
  ;
  
class_new:
  ( class_scope )? 'new' ( '(' list_of_arguments ')' )?
  | 'new' expression
  ;
  
dynamic_array_new: 
  'new' ( expression )? ( '(' expression ')' )?
  ; 

//***********************************************************************
//* A.2.5 Declaration ranges
//***********************************************************************
unpacked_dimension:
  '[' constant_range ']'
  | '[' constant_expression ']'
  ;
  
packed_dimension:
  '[' constant_range ']'
  | unsized_dimension
  ;
  
associative_dimension:
  '[' data_type ']'
  | '[' '*' ']'
  ;
  
variable_dimension:
  unsized_dimension
  | unpacked_dimension
  | associative_dimension
  | queue_dimension
  ;
  
queue_dimension: 
  '[' '$' ( ':' constant_expression )? ']'
  ;
  
unsized_dimension: 
  '[' ']'
  ;

//***********************************************************************
//* TODO: A.2.6 Function declarations
//***********************************************************************

//***********************************************************************
//* TODO: A.2.7 Task declarations
//***********************************************************************

//***********************************************************************
//* TODO: A.2.8 Block item declarations
//***********************************************************************

//***********************************************************************
//* TODO: A.2.9 Interface declarations
//***********************************************************************

//***********************************************************************
//* TODO: A.2.10 Assertion declarations
//***********************************************************************

//***********************************************************************
//* TODO: A.2.11 Covergroup declarations
//***********************************************************************

//***************************************************************************
//* A.3 Primitive instances
//***************************************************************************

//***********************************************************************
//* TODO: A.3.1 Primitive instantiation and instances
//***********************************************************************

//***********************************************************************
//* TODO: A.3.2 Primitive strengths
//***********************************************************************

//***********************************************************************
//* TODO: A.3.3 Primitive terminals
//***********************************************************************

//***********************************************************************
//* TODO: A.3.4 Primitive gate and switch types
//***********************************************************************

//***************************************************************************
//* A.4 Instantiations
//***************************************************************************

//*************************************************************************
//* A.4.1 Instantiation
//*************************************************************************

//***********************************************************************
//* A.4.1.1 Module instantiation
//***********************************************************************
module_instantiation:
  module_identifier ( parameter_value_assignment )? hierarchical_instance ( ',' hierarchical_instance )* ';'
  ;
  
parameter_value_assignment: 
  '#' '(' ( list_of_parameter_assignments )? ')'
  ;

list_of_parameter_assignments:
  ordered_parameter_assignment ( ',' ordered_parameter_assignment )*
  | named_parameter_assignment ( ',' named_parameter_assignment )*
  ;
  
ordered_parameter_assignment: 
  param_expression
  ;
  
named_parameter_assignment: 
  '.' parameter_identifier '(' ( param_expression )? ')'
  ;
  
hierarchical_instance: 
  name_of_instance '(' ( list_of_port_connections )? ')'
  ;
  
name_of_instance: 
  instance_identifier ( unpacked_dimension )*
  ;
  
list_of_port_connections:
  ordered_port_connection ( ',' ordered_port_connection )*
  | named_port_connection ( ',' named_port_connection )*
  ; 
ordered_port_connection: 
  ( attribute_instance )* ( expression )?
  ;
  
named_port_connection:
  ( attribute_instance )* '.' port_identifier ( '(' ( expression )? ')' )?
  | ( attribute_instance ) '.*'
  ;

//***********************************************************************
//* TODO: A.4.1.2 Interface instantiation
//***********************************************************************

//***********************************************************************
//* TODO: A.4.1.3 Program instantiation
//***********************************************************************

//***********************************************************************
//* TODO: A.4.1.4 Checker instantiation
//***********************************************************************

//*************************************************************************
//* A.4.2 Generated instantiation
//*************************************************************************

//***************************************************************************
//* A.4 UDP declaration and instantiation
//***************************************************************************

//*************************************************************************
//* A.5.1 UDP declaration
//*************************************************************************

//*************************************************************************
//* A.5.2 UDP ports
//*************************************************************************

//*************************************************************************
//* A.5.3 UDP body
//*************************************************************************

//*************************************************************************
//* A.5.4 UDP instantiation
//*************************************************************************

//***************************************************************************
//* A.6 Behavioral statements
//***************************************************************************

//*************************************************************************
//* TODO: A.6.1 Continuous assignment and net alias statements
//*************************************************************************

//*************************************************************************
//* TODO: A.6.2 Procedural blocks and assignments
//*************************************************************************

//*************************************************************************
//* TODO: A.6.3 Parallel and sequential blocks
//*************************************************************************

//*************************************************************************
//* TODO: A.6.4 Statements
//*************************************************************************

//*************************************************************************
//* TODO: A.6.5 Timing control statements
//*************************************************************************

//*************************************************************************
//* TODO: A.6.6 Conditional statements
//*************************************************************************

//*************************************************************************
//* TODO: A.6.7 Case statements
//*************************************************************************

//***********************************************************************
//* TODO: A.6.7.1 Patterns
//***********************************************************************

//*************************************************************************
//* TODO: A.6.8 Looping statements
//*************************************************************************

//*************************************************************************
//* TODO: A.6.9 Subroutine call statements
//*************************************************************************

//*************************************************************************
//* TODO: A.6.10 Assertion statements
//*************************************************************************

//*************************************************************************
//* TODO: A.6.11 Clocking block
//*************************************************************************

//*************************************************************************
//* TODO: A.6.12 Randsequence
//*************************************************************************

//***************************************************************************
//* A.7 Specify section
//***************************************************************************

//***************************************************************************
//* A.8 Expressions
//***************************************************************************

//*************************************************************************
//* A.8.1 Concatenations
//*************************************************************************

concatenation:
  '{' expression ( ',' expression )* '}'
  ;
  
constant_concatenation:
  '{' constant_expression ( ',' constant_expression )* '}'
  ;
  
constant_multiple_concatenation: 
  '{' constant_expression constant_concatenation '}'
  ;
  
module_path_concatenation: 
  '{' module_path_expression ( ',' module_path_expression )* '}'
  ;
  
module_path_multiple_concatenation: 
  '{' constant_expression module_path_concatenation '}'
  ;
  
multiple_concatenation: 
  '{' expression concatenation '}'
  ;
  
streaming_concatenation: 
  '{' stream_operator ( slice_size )? stream_concatenation '}'
  ;
  
stream_operator: 
  '>>' | '<<'
  ;
  
slice_size: 
  simple_type | constant_expression
  ;
  
stream_concatenation: 
  '{' stream_expression ( ',' stream_expression )* '}'
  ;
  
stream_expression: 
  expression ( 'with' '[' array_range_expression ']' )?
  ;
  
array_range_expression:
  expression
  | expression ':' expression
  | expression '+:' expression
  | expression '-:' expression
  ;
  
empty_queue: 
  '{' '}'
  ;

//*************************************************************************
//* A.8.2 Subroutine calls
//*************************************************************************
constant_function_call: 
  function_subroutine_call
  ;
  
tf_call: 
  ps_or_hierarchical_tf_identifier ( attribute_instance )* ( '(' list_of_arguments ')' )?
  ;
  
system_tf_call:
  system_tf_identifier ( '(' list_of_arguments ')' )? 
  | system_tf_identifier '(' data_type ( ',' expression )? ')'
  ;
  
subroutine_call:
  tf_call
  | system_tf_call
  | method_call
  | ( 'std' '::' )? randomize_call
  ;
  
function_subroutine_call: 
  subroutine_call
  ;
  
list_of_arguments:
  ( expression )? ( ',' ( expression )? )* ( ',' '.' identifier '(' ( expression )? ')' )*
  | '.' identifier '(' ( expression )? ')' ( ',' '.' identifier '(' ( expression )? ')' )*
  ;
  
method_call: 
  method_call_root '.' method_call_body
  ;

method_call_body:
  method_identifier ( attribute_instance )* ( '(' list_of_arguments ')' )?
  | built_in_method_call
  ;
  
built_in_method_call:
  array_manipulation_call
  | randomize_call
  ;
  
array_manipulation_call:
  array_method_name ( attribute_instance )*
  ( '(' list_of_arguments ')' )?
  ( 'with' '(' expression ')' )?
  ;
  
randomize_call:
  randomize ( attribute_instance )*
  ( '(' ( variable_identifier_list | null )? ')' )?
  ( 'with' ( '(' ( identifier_list )? ')' )? constraint_block )?
  ;
  
method_call_root: 
  primary | implicit_class_handle
  ;
  
array_method_name:
  method_identifier | 'unique' | 'and' | 'or' | 'xor'
  ;
  
//*************************************************************************
//* A.8.3 Expressions
//*************************************************************************
inc_or_dec_expression:
  inc_or_dec_operator ( attribute_instance )* variable_lvalue
  | variable_lvalue ( attribute_instance )* inc_or_dec_operator
  ;
  
conditional_expression: 
  cond_predicate '?' ( attribute_instance )* expression ':' expression
  ;
  
constant_expression:
  constant_primary
  | unary_operator ( attribute_instance )* constant_primary
  | constant_expression binary_operator ( attribute_instance )* constant_expression
  | constant_expression '?' ( attribute_instance )* constant_expression ':' constant_expression
  ;
  
constant_mintypmax_expression:
  constant_expression
  | constant_expression ':' constant_expression ':' constant_expression
  ;
  
constant_param_expression:
  constant_mintypmax_expression | data_type | '$'
  ;
  
param_expression: 
  mintypmax_expression | data_type | '$'
  ;
  
constant_range_expression:
  constant_expression
  | constant_part_select_range
  ;
  
constant_part_select_range:
  constant_range
  | constant_indexed_range
  ;
  
constant_range: 
  constant_expression ':' constant_expression
  ;
  
constant_indexed_range:
  constant_expression '+:' constant_expression
  | constant_expression '-:' constant_expression
  ;
  
expression:
  primary
  | unary_operator ( attribute_instance )* primary
  | inc_or_dec_expression
  | '(' operator_assignment ')'
  | expression binary_operator ( attribute_instance )* expression
  | conditional_expression
  | inside_expression
  | tagged_union_expression
  ;
  
tagged_union_expression:
  'tagged' member_identifier ( expression )?
  ;
  
inside_expression: 
  expression 'inside' '{' open_range_list '}'
  ;
  
value_range:
  expression
  | '[' expression ':' expression ']'
  ;
  
mintypmax_expression:
  expression
  | expression ':' expression ':' expression
  ;
  
module_path_conditional_expression: 
  module_path_expression '?' ( attribute_instance )* module_path_expression ':' module_path_expression
  ; 
  
module_path_expression:
  module_path_primary
  | unary_module_path_operator ( attribute_instance )* module_path_primary
  | module_path_expression binary_module_path_operator ( attribute_instance )* module_path_expression
  | module_path_conditional_expression
  ; 
  
module_path_mintypmax_expression:
  module_path_expression
  | module_path_expression ':' module_path_expression ':' module_path_expression
  ;
  
part_select_range: 
  constant_range | indexed_range
  ;
  
indexed_range:
  expression '+:' constant_expression
  | expression '-:' constant_expression
  ;
  
genvar_expression: 
  constant_expression 
  ;

//*************************************************************************
//* A.8.4 Primaries
//*************************************************************************
constant_primary:
  primary_literal
  | ps_parameter_identifier constant_select
  | specparam_identifier ( '[' constant_range_expression ']' )?
  | genvar_identifier
  | formal_port_identifier constant_select 
  | ( package_scope | class_scope )? enum_identifier
  | constant_concatenation ( '[' constant_range_expression ']' )?
  | constant_multiple_concatenation ( '[' constant_range_expression ']' )?
  | constant_function_call
  | constant_let_expression
  | '(' constant_mintypmax_expression ')'
  | constant_cast
  | constant_assignment_pattern_expression
  | type_reference
  ;
  
module_path_primary:
  number
  | identifier
  | module_path_concatenation
  | module_path_multiple_concatenation
  | function_subroutine_call
  | '(' module_path_mintypmax_expression ')'
  ;
  
primary:
  primary_literal
  | ( class_qualifier | package_scope )? hierarchical_identifier select
  | empty_queue
  | concatenation ( '[' range_expression ']' )?
  | multiple_concatenation ( '[' range_expression ']' )?
  | function_subroutine_call
  | let_expression
  | '(' mintypmax_expression ')'
  | cast
  | assignment_pattern_expression
  | streaming_concatenation
  | sequence_method_call
  | 'this'
  | '$'
  | 'null'
  ; 
  
class_qualifier: 
  ( 'local' '::' )? ( implicit_class_handle '.' | class_scope )?
  ;
  
range_expression:
  expression
  | part_select_range
  ;
  
primary_literal: 
  number 
  | time_literal 
  | unbased_unsized_literal 
  | string_literal
  ;
  
time_literal:
  unsigned_number time_unit
  | fixed_point_number time_unit
  ;
  
time_unit: 
  's' 
  | 'ms' 
  | 'us' 
  | 'ns' 
  | 'ps' 
  | 'fs'
  ;
  
implicit_class_handle: 
  'this' 
  | 'super' 
  | 'this' '.' 'super'
  ;
  
bit_select: 
  '{' ( expression )? '}'
  ;
  
select:
  ( '{' '.' member_identifier bit_select '}' '.' member_identifier )? bit_select ( '[' part_select_range ']' )?
  ;
  
nonrange_select:
  ( '{' '.' member_identifier bit_select '}' '.' member_identifier )? bit_select
  ;
  
constant_bit_select: 
  '{' ( constant_expression )? '}'
  ;
  
constant_select:
  ( '{' '.' member_identifier constant_bit_select '}' '.' member_identifier )? constant_bit_select
    ( '[' constant_part_select_range ']' )?
  ;
  
constant_cast:
  casting_type '\'' '(' constant_expression ')'
  ;
  
constant_let_expression: 
  let_expression
  ;
  
cast:
  casting_type '\'' '(' expression ')'
  ;
  
//***********************************************************************
//* A.8.5 Expression left-side values
//***********************************************************************
net_lvalue:
  ps_or_hierarchical_net_identifier constant_select
  | '{' net_lvalue ( ',' net_lvalue )* '}'
  | ( assignment_pattern_expression_type )? assignment_pattern_net_lvalue
  ;
  
variable_lvalue:
  ( implicit_class_handle '.' | package_scope )? hierarchical_variable_identifier select
  | '{' variable_lvalue ( ',' variable_lvalue )* '}'
  | ( assignment_pattern_expression_type )? assignment_pattern_variable_lvalue
  | streaming_concatenation
  ;
  
nonrange_variable_lvalue:
  ( implicit_class_handle '.' | package_scope )? hierarchical_variable_identifier nonrange_select 
  ;

//***********************************************************************
//* A.8.6 Operators
//***********************************************************************
unary_operator:
  '+' | '-' | '!' | '~' | '&' | '~&' | '|' | '~|' | '^' | '~^' | '^~'
  ;
  
binary_operator:
  '+' | '-' | '*' | '/' | '%' | '==' | '!=' | '===' | '!==' | '==?' | '!=?' | '&&' | '||' | '**'
  | '<' | '<=' | '>' | '>=' | '&' | '|' | '^' | '^~' | '~^' | '>>' | '<<' | '>>>' | '<<<'
  | '->' | '<->'
  ;
  
inc_or_dec_operator: 
  '++' | '--'
  ;
  
unary_module_path_operator:
  '!' | '~' | '&' | '~&' | '|' | '~|' | '^' | '~^' | '^~'
  ;
  
binary_module_path_operator:
  '==' | '!=' | '&&' | '||' | '&' | '|' | '^' | '^~' | '~^'
  ;
 
//***********************************************************************
//* TODO: A.8.7 Numbers
//***********************************************************************

//***********************************************************************
//* A.8.8 Strings
//***********************************************************************

string_literal: DOUBLE_QUOTED_STRING ;

DOUBLE_QUOTED_STRING : '"' (~ [\n\r])* '"';

//***********************************************************************
//* A.9 General
//***********************************************************************

// A.9.1 Attributes
attribute_instance : 
	'(*' attr_spec ( ',' attr_spec )* '*)'
	;
	
attr_spec : 
	attr_name ( '=' constant_expression )?
	;
	
attr_name : identifier ;

// A.9.2 Comments
WS : [ \t\n\r]+ -> channel (HIDDEN) ;
 
SL_COMMENT 	: '//' .*? '\r'? ('\n'|EOF) -> channel (HIDDEN) ;

ML_COMMENT	: '/*' .*? '*/' -> channel (HIDDEN) ;

//***********************************************************************
//* A.9.3  Identifiers
//***********************************************************************
array_identifier: identifier;
block_identifier: identifier;
bin_identifier: identifier;
C_IDENTIFIER: [a-zA-Z_] [a-zA-Z0-9_]*;
c_identifier: C_IDENTIFIER ; 
cell_identifier: identifier;
checker_identifier: identifier;
class_identifier: identifier;
class_variable_identifier: variable_identifier;
clocking_identifier: identifier;
config_identifier: identifier;
const_identifier: identifier;
constraint_identifier: identifier;
covergroup_identifier: identifier;
covergroup_variable_identifier: variable_identifier;
cover_point_identifier: identifier;
cross_identifier: identifier;
dynamic_array_variable_identifier: variable_identifier;
enum_identifier: identifier;
ESCAPED_ID : '\\' ('\u0021'..'\u007E')+ ~ [ \r\t\n]* ;
escaped_identifier: ESCAPED_ID;
formal_identifier: identifier;
formal_port_identifier: identifier;
function_identifier: identifier;
generate_block_identifier: identifier;
genvar_identifier: identifier;
hierarchical_array_identifier: hierarchical_identifier;
hierarchical_block_identifier: hierarchical_identifier;
hierarchical_event_identifier: hierarchical_identifier;
hierarchical_identifier: ( '$root' '.' )? ( identifier constant_bit_select '.' )* identifier;
hierarchical_net_identifier: hierarchical_identifier;
hierarchical_parameter_identifier: hierarchical_identifier;
hierarchical_property_identifier: hierarchical_identifier;
hierarchical_sequence_identifier: hierarchical_identifier;
hierarchical_task_identifier: hierarchical_identifier;
hierarchical_tf_identifier : hierarchical_identifier;

hierarchical_variable_identifier : hierarchical_identifier;

identifier :
simple_identifier
| escaped_identifier;

index_variable_identifier : identifier;
interface_identifier : identifier;
interface_instance_identifier : identifier;
inout_port_identifier : identifier;
input_port_identifier : identifier;
instance_identifier : identifier;
library_identifier : identifier;
member_identifier : identifier;
method_identifier : identifier;
modport_identifier : identifier;
module_identifier : identifier;
net_identifier : identifier;
net_type_identifier : identifier;
output_port_identifier : identifier;
package_identifier : identifier;

package_scope :
	package_identifier '::'
	| '$unit' '::'
	;
parameter_identifier : identifier;
port_identifier : identifier;
production_identifier : identifier;
program_identifier : identifier;
property_identifier : identifier;
ps_class_identifier : ( package_scope )? class_identifier;
ps_covergroup_identifier : ( package_scope )? covergroup_identifier;
ps_checker_identifier : ( package_scope )? checker_identifier;
ps_identifier : ( package_scope )? identifier;
ps_or_hierarchical_array_identifier :
	( implicit_class_handle '.' | class_scope | package_scope )? hierarchical_array_identifier
	ps_or_hierarchical_net_identifier ':' ( package_scope )? net_identifier | hierarchical_net_identifier
	;
	
ps_or_hierarchical_property_identifier :
	( package_scope )? property_identifier
	| hierarchical_property_identifier
	;
	
ps_or_hierarchical_sequence_identifier :
	( package_scope )? sequence_identifier
	| hierarchical_sequence_identifier
	;
	
ps_or_hierarchical_tf_identifier :
	( package_scope )? tf_identifier
	| hierarchical_tf_identifier
	;
	
ps_parameter_identifier : 
	( package_scope | class_scope )? parameter_identifier
	| ( generate_block_identifier ( '[' constant_expression ']' )? '.' )* parameter_identifier
	;

ps_type_identifier : 
  ( 'local' '::' | package_scope )? type_identifier
  ;
  
sequence_identifier : 
  identifier
  ;
  
signal_identifier : 
  identifier
  ;

ID : 
  [a-zA-Z_][a-zA-Z0-9_$]* 
  ;

simple_identifier : 
  ID 
  ;
  
specparam_identifier : identifier;
STF_ID : 
  [$][a-zA-Z0-9_$][a-zA-Z0-9_$]*
  ;
  
system_tf_identifier : 
  STF_ID 
  ;
  
task_identifier : identifier;
tf_identifier : identifier;
terminal_identifier : identifier;
topmodule_identifier : identifier;
type_identifier : identifier;
udp_identifier : identifier;
variable_identifier : identifier;

