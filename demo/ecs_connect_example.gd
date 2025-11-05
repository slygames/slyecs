extends Node

#@export var sprite_2d: Sprite2D

@onready var sprite_2d: Sprite2D = $Sprite2D

@export var components : Array[Component]


func _ready() -> void:

	#Ecs.connect(get_tree())
	Ecs.create_entity(sprite_2d, components)
	#Ecs.create_entity(sprite_2d, [new_component, new_component2])
