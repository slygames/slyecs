extends Node

#@export var sprite_2d: Sprite2D

@onready var sprite_2d: Sprite2D = $Sprite2D

const new_component = preload("uid://cc8ujoq0m5xl1")
const new_component2 = preload("uid://cc8ujoq0m5xl1")

func _ready() -> void:

	#Ecs.connect(get_tree())
	
	var components : Array[Component]
	components.push_back(new_component)
	#Ecs.create_entity(sprite_2d, components)
	
	Ecs.create_entity(sprite_2d, [new_component, new_component2])
	#Ecs.create_entity(sprite_2d)
	#Ecs.create_entity(sprite_2d,[new_component]);
	#Ecs.remove_entity(sprite_2d)
