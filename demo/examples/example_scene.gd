extends Node

#@export var sprite_2d: Sprite2D
#
#@onready var sprite_2d: Sprite2D = $Sprite2D

#@export var components : Array[Component]

#@export var Component_Value_Example : Variant

func _ready() -> void:
	pass
	#Ecs.connect(get_tree())
	#Ecs.create_entity(sprite_2d, components)
	#Ecs.create_entity(sprite_2d, [new_component, new_component2])
	
	
	#Ecs.create_entity(sprite_2d)
	#_create_systems()

	#system_movement.components

func _create_systems():
	pass
	#var system_movement_callable = Callable(_system_movement_update)
	#var system_movement = System.new()	
#
	#var system_render_callable = Callable(_system_render_update)
	#var system_render = System.new()
	#
	#var system_spawn_callable = Callable(_system_spawn_update)
	#var system_spawn = System.new()
	
func _system_movement_update():
	#self.entities
	print("_system_movement_update called")
	pass
	
