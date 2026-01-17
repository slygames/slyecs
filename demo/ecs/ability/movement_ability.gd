extends Ability

func _update():
	
	set_attribute_val("bool_attr",true)
	
	print("BOOL DICTIONARY")
	
	#print("LABEL IS ", get_attribute_val("label")
	var bool_dict : Dictionary = get_attribute_val("bool_attr")
	var bool_val : bool = false
	
	for entity_id in bool_dict:
		bool_val = bool_dict[entity_id]
		#print("ENTITY ", entity_id, " : BOOL_ATTR ", bool_dict[entity_id])
		print("ENTITY ", entity_id, " : BOOL_ATTR ", bool_val)
	pass
	
	##print("gdscript adding..")
	##print(">>> ability id ", get_instance_id())
	##print(">> attrib reqd", attributes_required[0]);
	##
	##var attribute1 : Attribute = get_attribute("velocity")
	##var attribute2 : Attribute = get_attribute("velocity")
	##var attribute3 : Attribute = get_attribute("velocity")
##
	##print("attribute1 ::: ", attribute1.get_attribute_name())
	##print("here1")
	##print("attribute2 ::: ", attribute2.get_attribute_name())
	##print("here2")
	##print("attribute3 ::: ", attribute3.get_attribute_name())
	##
	##print("here3")
	#
	####get_attribute("label").set_val("XYZ")
	##get_attribute("label").add(StringName("DEF"));
	##get_attribute("label").add(StringName("GHQ"));
	##
	##print("LABEL DICTIONARY")
	##
	##var label_dict : Dictionary = get_attribute_val("label")
	##
	###var label_dict : Dictionary[int, Variant] = get_attribute_val("label")
	##
	##for entity_id in label_dict:
		##print("ENTITY ", entity_id, " : LABEL ", label_dict[entity_id])
#
	##set_attribute_val("velocity", 7.0)
	##get_attribute("velocity").set_var(5)
	#get_attribute("velocity").add(3.5)
	#get_attribute("velocity").add(1)
	##get_attribute("velocity").add(2)
#
	### Add to another velocity attribute so the value must double, for testing attribute + attribute
	##var velocity_sum_attribute : Attribute
	##velocity_sum_attribute = velocity_sum_attribute.add(get_attribute("velocity"))
#
	#get_attribute("velocity").add(get_attribute("velocity"))
#
	#print("VELOCITY DICTIONARY")
	#
	##print("LABEL IS ", get_attribute_val("label")
	#var velocity_dict : Dictionary = get_attribute_val("velocity")
#
	#for entity_id in velocity_dict:
		#print("ENTITY ", entity_id, " : VELOCTY ", velocity_dict[entity_id])
	#
	#print("YOYO")
	#
	##print("VELOCITY IS ", vel)
		#
	##if attribute:
	#
	#
	##if attribute:
	##	print("gdscript adding..")
	##	attribute.add(150.55)
#
	##print("QQ1")
	##get_attribute("velocity").add(150.55)
	##print("QQ2")
	##get_attribute("velocity").add(125.33)
#
	##print("QZ0")
	##set_attribute_val("velocity", 100.0)
	##print("QQ0")
	##set_attribute_val("velocity", 300.0)
	##set_attribute_val("velocity", 1510.0)
	##print("QQ3")
	##print("QQ4")
	##get_attribute("velocity").add(3.77)
	##print("QQ5")
	##set_attribute_val("velocity", 500.0)
	##print("_update for movement system called from gdscript")
	##set_attribute_val("position", "velocity", "*","position")
	##var velocity_attr : Attribute = get_attribute("velocity")
	##velocity_attr.set_var(entity_list)
	##components_required[0] = (Transform3D)components_required[0].data_var.x
	## * components_required[1]
	##singleton : Ecs = Ecs.get_singleton()
#
	#pass

#
#func _movement_system():
#	print("movement system called from gdscript")
#	pass
#
