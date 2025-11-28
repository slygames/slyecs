extends Ability

func _update():
	set_attribute_val("velocity", 500.0)
	
	
	#print("_update for movement system called from gdscript")
	
	#set_attribute_val("position", "velocity", "*","position")

	#var velocity_attr : Attribute = get_attribute("velocity")
	#velocity_attr.set_var(entity_list)
	
	
	#components_required[0] = (Transform3D)components_required[0].data_var.x
	# * components_required[1]

	#singleton : Ecs = Ecs.get_singleton()
	pass

#
#func _movement_system():
#	print("movement system called from gdscript")
#	pass
#
