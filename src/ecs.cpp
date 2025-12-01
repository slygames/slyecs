#include "ecs.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace sly {

//map<Ability*> Ability::abilities; //todo:remove

//TypedArray<Ability> Ecs::abilities;

//array<Ability*> Ecs::abilities;

/*
map<Object*> Ecs::object_map;
map<Archetype*> Ecs::archetype_map;
map<Attribute*> Ecs::attribute_map;
//map<StringName> Ecs::tag_map;
*/

// initialize static variables
Ecs* Ecs::singleton = nullptr;

//map<Ability*> Ecs::abilities;
//map<Attribute*> Ecs::attribute_register;
//map<StringName> Ecs::attribute_name_register;

void Ecs:: _bind_methods() {
	//ClassDB::bind_static_method("Ecs", D_METHOD("get_singleton"), &Ecs::get_singleton);
	ClassDB::bind_method(D_METHOD("connect", "scene_tree"), &Ecs::connect);
	
	/*
	//todo:add
	//ClassDB::bind_method(D_METHOD("create_archetype", "object", "attributes"), &Ecs::register_archetype, DEFVAL(TypedArray<Attribute>()));
	ClassDB::bind_method(D_METHOD("create_archetype", "archetype"), &Ecs::register_object);
	ClassDB::bind_method(D_METHOD("remove_archetype", "archetype"), &Ecs::unregister_object);
	*/

	/*
	ClassDB::bind_method(D_METHOD("set_abilities", "p_abilities"), &Ecs::set_abilities);
	ClassDB::bind_method(D_METHOD("get_abilities"), &Ecs::get_abilities);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "abilities", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Ability"), "set_abilities", "get_abilities");
	*/

	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "abilities", PROPERTY_HINT_ARRAY_TYPE, "Ability"), "set_abilities", "get_abilities");

}

void NodeECS::_bind_methods() {
/*
	ClassDB::bind_method(D_METHOD("set_archetype", "p_archetype"), &NodeECS::set_archetype);
	ClassDB::bind_method(D_METHOD("get_archetype"), &NodeECS::get_archetype);
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, "archetype", godot::PROPERTY_HINT_RESOURCE_TYPE, "Archetype"), "set_archetype", "get_archetype");
*/

	ClassDB::bind_method(D_METHOD("set_abilities", "abilities"), &NodeECS::set_abilities);
	ClassDB::bind_method(D_METHOD("get_abilities"), &NodeECS::get_abilities);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "abilities", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Ability"), "set_abilities", "get_abilities" );

	/*
	ClassDB::bind_method(D_METHOD("set_attributes", "p_attributes"), &NodeECS::set_attributes);
	ClassDB::bind_method(D_METHOD("get_attributes"), &NodeECS::get_attributes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes", "get_attributes");

	ClassDB::bind_method(D_METHOD("set_archetypes", "p_archetypes"), &NodeECS::set_archetypes);
	ClassDB::bind_method(D_METHOD("get_archetypes"), &NodeECS::get_archetypes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "archetypes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Archetype"), "set_archetypes", "get_archetypes");
	*/
/*
	ClassDB::bind_method(D_METHOD("set_attributes", "p_attributes"), &NodeEcs::set_attributes);
	ClassDB::bind_method(D_METHOD("get_attributes"), &NodeEcs::get_attributes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes", "get_attributes");
*/

/*
	ClassDB::bind_method(D_METHOD("set_attributes", "p_attributes"), &NodeECS::set_attributes);
	ClassDB::bind_method(D_METHOD("get_attributes"), &NodeECS::get_attributes);
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "attributes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + "StringName,Attribute"), "set_attributes", "get_attributes");
*/

	ClassDB::bind_method(D_METHOD("set_tags", "tags"), &NodeECS::set_tags);
	ClassDB::bind_method(D_METHOD("get_tags"), &NodeECS::get_tags);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags", "get_tags" );
}

void NodeECS::_notification(int p_what) {
	//print("what", p_what);
	
	//todo: this seems to do nothing.
	print("NodeEcs::_notification is_editor_hint()", godot::Engine::get_singleton()->is_editor_hint());
	if(godot::Engine::get_singleton()->is_editor_hint()) {
		print("is_editor_hint() is TRUE");
		return; // do nothing in the editor
	}

	switch(p_what) {
		/*
		case NOTIFICATION_READY:
			// create entity
			Entity* new_entity = Ecs::get_singleton()->create_entity(this->get_parent());
			break;
		*/
		//case NOTIFICATION_READY: {

		case NOTIFICATION_ENTER_TREE: {
			print("NOTIFICATION_ENTER_TREE");
			// create entity
			Object* entity = this->get_parent();
			int64_t entity_id = Ecs::get_singleton()->create_entity(entity);
			print("created entity ", entity_id);
			print("abilities size ", abilities.size());
			// grant default abilities
			for(int i=0; i<abilities.size();i++) {
				Ability* ability = cast_to<Ability>(abilities[i]);
				// assign entity to ability
				ability->entities_assigned.insert(entity_id);
				ability->entities_approved.insert(entity_id);

				// add to Ecs abilities if not registered yet
				if(!Ecs::get_singleton()->ability_register.has(ability)) {
					Ecs::get_singleton()->ability_register.insert(ability);	// all abilities added to the Ecs
					// insert attributes for this ability
					const TypedArray<Attribute>& attributes = ability->get_attributes_required();
					for(int j=0;j<attributes.size();j++) {
						Attribute* attribute = cast_to<Attribute>(attributes[i]);
						attribute->get_attribute_data()->var_type = attribute->data_var.get_type();
						//todo:BUG how does this prevent duplicates in these registers?! it doesnlt.. bug
						if(!Ecs::get_singleton()->attribute_register.has(attribute)) {
							Ecs::get_singleton()->create_attribute(attribute);
						}

						attribute->create_attribute_data_entry(entity_id);

						//todo:set_attribute_val() should proabbly be part of Ecs class? but then how to call this from update?! an attribute isn't stricly part of an ability, multiple abilties can share the smae attribute, so this doesn't make sense in ability.
						// set attribute default value
						//ability->set_attribute_val(attribute->get_attribute_name(), attribute->data_var);

						attribute->get_attribute_data()->debug_print();
					}
				}
				print("Ecs Abilities Size : ", Ecs::get_singleton()->ability_register.size());
				Ecs::get_singleton()->grant_abliity(entity, ability);
				print("path ", ability->get_path(), "ability ", ability->get_ability_name(), " added to entity ", this->get_parent()->get_name(), " total: ", ability->entities_assigned.size());
			}
		} break;
		//case NOTIFICATION_WM_CLOSE_REQUEST: {
		case NOTIFICATION_EXIT_TREE: {
			print("NOTIFICATION_EXIT_TREE");
			Object* entity = this->get_parent();
			// revoke default abilities
			for(int i=0; i<abilities.size();i++) {
				Ability* ability = cast_to<Ability>(abilities[i]);
				Ecs::get_singleton()->revoke_ability(entity, ability);
				//todo:bug these shouldn't be removed if there's any entities using this, may need a count or simplify this.
				// remove attributes for this ability
				const TypedArray<Attribute>& attributes = ability->get_attributes_required();
				for(int j=0;j<attributes.size();j++) {
					Attribute* attribute = cast_to<Attribute>(attributes[i]);
					Ecs::get_singleton()->attribute_register.remove(attribute);
					Ecs::get_singleton()->attribute_name_register.remove(attribute->get_attribute_name());
				}

			}
			// remove entity
			Ecs::get_singleton()->remove_entity(entity);
		} break;

		/*
			// register parent of NodeEcs as the game object
			Ecs::get_singleton()->register_object(this->get_parent());
		*/

//todo:enable
/*			
			// get unique set of all attributes from archetypes
			std::set<Attribute*> object_attributes;
			for(int i=0;i<archetypes.size();i++) {
				Archetype* archetype = cast_to<Archetype>(archetypes[i]);
				TypedArray<Attribute> archetype_attributes = archetype->get_attributes();
				for(int j=0;j<archetype_attributes.size();j++) {
					Attribute* attribute = cast_to<Attribute>(archetype_attributes[j]);
					object_attributes.insert(attribute);
				}
			}
			// also get attributes arrays specified in the NodeEcs
			for(int i=0;i<attributes.size();i++) {
				Attribute* attribute = cast_to<Attribute>(attributes[i]);
				object_attributes.insert(attribute);
			}
*/
			/*
			for(int i=0;i<object_attributes.size();i++) {
				object_attributes.data_var
			}*/

			//todo: need to create all the data rows for the attributes for this object and also associate the tags with the object.

			break;
	}
}

#if 0
void Archetype::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_attributes", "p_attributes"), &Archetype::set_attributes);
	ClassDB::bind_method(D_METHOD("get_attributes"), &Archetype::get_attributes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes", "get_attributes");
/*
	ClassDB::bind_method(D_METHOD("set_parents", "p_parents"), &Archetype::set_parents);
	ClassDB::bind_method(D_METHOD("get_parents"), &Archetype::get_parents);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "parents", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Archetype"), "set_parents", "get_parents");
*/
	//ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "attributes", PROPERTY_HINT_DICTIONARY_TYPE, "Variant::STRING_NAME, Attribute"), "set_attributes", "get_attributes");
	
	//todo:this maybe useful TYPED_DICTIONARY
	/*
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "attributes", PROPERTY_HINT_TYPE_STRING, String::num(Variant::STRING_NAME) + ":;" + String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":" + "Attribute", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_SCRIPT_VARIABLE), "set_attributes", "get_attributes");
	*/

/*
	ClassDB::bind_method(D_METHOD("set_tags", "tags"), &Archetype::set_tags);
	ClassDB::bind_method(D_METHOD("get_tags"), &Archetype::get_tags);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags", "get_tags" );
*/

	/*
	ClassDB::bind_method(D_METHOD("set_nodes", "p_nodes"), &Archetype::set_nodes);
	ClassDB::bind_method(D_METHOD("get_nodes"), &Archetype::get_nodes);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "nodes", PROPERTY_HINT_NODE_TYPE, "Node"), "set_nodes", "get_nodes");
	*/

	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes", PROPERTY_HINT_ARRAY_TYPE, "Variant::Attribute"), "set_attributes", "get_attributes" );
	
	//PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Image")
}

Archetype::Archetype() {
	/*
	print("CONSTRUCT archetype");
	Ecs::archetype_map.insert(this);
	print("archetype map size A: ", Ecs::attribute_map.size());
	*/
}
#endif

/*
Attribute::Attribute() {
	print("CONSTRUCT attribute");
	Ecs::attribute_map.insert(this);
	print("comp map size A: ", Ecs::attribute_map.size());
}
*/

void Ecs::create_attribute(Attribute* attribute) {
	Ecs* ecs = get_singleton();
	if(!ecs->attribute_register.has(attribute)) {
		ecs->attribute_register.insert(attribute);
		ecs->attribute_name_register.insert(attribute->get_attribute_name());
		//attribute->create_attribute_data_entry();
	}
}

void Ecs::remove_attribute(Attribute* attribute) {
	Ecs* ecs = get_singleton();
	if(ecs->attribute_register.has(attribute)) {
		ecs->attribute_name_register.remove(attribute->get_attribute_name());
		ecs->attribute_register.remove(attribute);
	}
}


void Attribute::set_data_var(const Variant &p_data_var) {
		if(&p_data_var!=nullptr) { 
			data_var = p_data_var;
		}
/*
		switch(data_var.get_type()) {
			case Variant::BOOL:
				data_array = sly::array<bool>();
				break;
			case Variant::INT:
				data_array = sly::array<int>();
				break;
			case Variant::FLOAT:
				data_array = sly::array<float>();
				break;
			case Variant::STRING:
				data_array = sly::array<String>();
				break;
			case Variant::STRING_NAME:
				data_array = sly::array<StringName>();
				break;
			//todo: add other cases for primitive types
			default:
				data_array = sly::array<Variant>();
		}
*/	
		emit_changed(); // for Resources to notify the editor/users of changes
}

/*
const Variant &Attribute::get_data_var() const {
	return data_var; // get value (does conversion to_var())
}*/

Ability::Ability() : is_enabled(true) {
	//notification(NOTIFICATION_POSTINITIALIZE);
	/*
	abilities.insert(this);
	print("instance id:", this->get_instance_id());
	Ability* obj = cast_to<Ability>(UtilityFunctions::instance_from_id(this->get_instance_id()));
	print("obj id: ", obj->get_instance_id());
	print("abilities size ", abilities.size());
	*/
	//print("running ability constructor");
	//Ecs::get_singleton()->increment_testint(ability_name);
	//Ecs::get_singleton()->increment_testint(this->get_path());
}


void Ability::set_attribute_val(StringName attribute_name, Variant value) {
	/*
	print("path ", get_path(), "ability ", get_ability_name(), "set_attribute_val() : entities assigned size: ", entities_assigned.size());
	print("path ", get_path(), "ability ", get_ability_name(), "set_attribute_val() : entities approved size: ", entities_approved.size());
	int attr_key = Ecs::get_singleton()->attribute_name_register.find[attribute_name];
	print("2aa ", Ecs::get_singleton()->attribute_register.size(), " : ", Ecs::get_singleton()->attribute_name_register.size());
	print("2a ", attr_key);
	Attribute* attribute = Ecs::get_singleton()->attribute_register[attr_key];
	print("2b");
	*/
	Attribute* attribute = get_attribute(attribute_name);
	// if decimals not entered a float value it may be considered an int, so to resolve this
	if(attribute->get_data_var().get_type()==Variant::FLOAT && value.get_type()!=Variant::FLOAT) {
		value =  (float)value;	// casting explicitly to float incase an int was passed into a float var
	}
	print("setting attribute value");
	// set value on all entities
	for(int entity_id : entities_approved) {
		print("setting attribute value entity ", entity_id);
		Variant val = attribute->get_attribute_data()->get_var(entity_id);
		print(entity_id, " ", attribute->get_attribute_name(), " : val : ", val);
		
		attribute->get_attribute_data()->set_var(entity_id, value);
		/*
		print("2bb ", attribute->get_attribute_name());
		print("ability_id ", get_instance_id(), "ability ", get_ability_name(), "set attribute ", attribute_name, " to ", attribute->get_attribute_data()->get_var(entity_id));
		print("2c");
		*/
	}
	//print("2d");
}

/*
Variant Ability::get_attribute_val(StringName attribute_name) {
	Attribute* attribute = get_attribute(attribute_name);

	return val;
}*/

Attribute* Ability::get_attribute(StringName attribute_name) {
	int attr_key = Ecs::get_singleton()->attribute_name_register.find[attribute_name];
	Attribute* attribute = Ecs::get_singleton()->attribute_register[attr_key];
	return attribute;
}

/**
 * registers attributes with the Ecs
 */
void Ability::initialize() {
	print("INitializeing ability ", get_path());
	for(int i=0; i<attributes_required.size(); i++) {
		Attribute* attr = cast_to<Attribute>(attributes_required[i]);
		Ecs::get_singleton()->attribute_register.insert(attr);
		/*
		print("get attribute name : ", attr->get_attribute_name());
		print("attr name", attr->get_name());
		print("attr path", attr->get_path());
		*/
		Ecs::get_singleton()->attribute_name_register.insert(attr->get_attribute_name());
	}
}

/*
Ability::~Ability() {
	//abilities.remove(this);
}*/

/*
Ability::_notification(int p_what) {
	switch(p_what) {
		case NOTIFICATION_READY:
		Ecs::get_singleton()->ability_register.insert(this);
		print("ability registered");
		break;
	}
}
*/

void Attribute::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_data_var", "data_var"), &Attribute::set_data_var);
	ClassDB::bind_method(D_METHOD("get_data_var"), &Attribute::get_data_var);
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");
	ADD_PROPERTY(PropertyInfo(Variant::NIL, "gd_data_var", PROPERTY_HINT_NONE, "Variant", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");

	ClassDB::bind_method(D_METHOD("set_attribute_name", "attribute_name"), &Attribute::set_attribute_name);
	ClassDB::bind_method(D_METHOD("get_attribute_name"), &Attribute::get_attribute_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "attribute_name"), "set_attribute_name", "get_attribute_name");


	/*
	ClassDB::bind_method(D_METHOD("set_data_var", "p_data_var"), &Attribute::set_data_var);
	ClassDB::bind_method(D_METHOD("get_data_var"), &Attribute::get_data_var);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data_var_array", PROPERTY_HINT_TYPE_STRING, String::num(Variant::NIL)+ "/" + String::num(PROPERTY_HINT_NONE) + ":Variant"), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data_var", PROPERTY_HINT_NONE, "Variant", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");
	*/


	/*
	ClassDB::bind_method(D_METHOD("set_data_var", "p_data_var"), &Attribute::set_data_var);
	ClassDB::bind_method(D_METHOD("get_data_var"), &Attribute::get_data_var);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "my_variant_array", PROPERTY_HINT_TYPE_STRING, String::num(Variant::NIL)), "set_data_var", "get_data_var");
*/
	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "data_var", PROPERTY_HINT_ARRAY_TYPE, "Variant", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_NIL_IS_VARIANT ), "set_data_var", "get_data_var");
	
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var"), "set_data_var", "get_data_var");
	//ADD_PROPERTY(PropertyInfo(Variant::NIL, "data_var", PROPERTY_HINT_TYPE_STRING, String::num(Variant::NIL) + "/" + String::num(PROPERTY_HINT_NONE) + ":Variant"), "set_data_var", "get_data_var");
}

/*
void Ability::_notification(int p_what) {
	print("ABILITY NOTIFICATION ", p_what);
	switch(p_what) {
		case NOTIFICATION_POSTINITIALIZE:
			print("running ability constructor");
			Ecs::get_singleton()->increment_testint(get_name());
			//Ecs::get_singleton()->ability_register.insert(this);
			break;
	}
}*/

void Ability::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update"), &Ability::update);
	GDVIRTUAL_BIND(_update);

	ClassDB::bind_method(D_METHOD("set_is_enabled", "p_is_enabled"), &Ability::set_is_enabled);
	ClassDB::bind_method(D_METHOD("get_is_enabled"), &Ability::get_is_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_enabled"), "set_is_enabled", "get_is_enabled");

	//ADD_PROPERTY(PropertyInfo(Variant::BOOL, "toggled"), "set_toggled", "is_toggled");

	ClassDB::bind_method(D_METHOD("set_attributes_required", "p_attributes_required"), &Ability::set_attributes_required);
	ClassDB::bind_method(D_METHOD("get_attributes_required"), &Ability::get_attributes_required);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes_required", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes_required", "get_attributes_required");

	ClassDB::bind_method(D_METHOD("set_attributes_forbidden", "p_attributes_forbidden"), &Ability::set_attributes_forbidden);
	ClassDB::bind_method(D_METHOD("get_attributes_forbidden"), &Ability::get_attributes_forbidden);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes_forbidden", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes_forbidden", "get_attributes_forbidden");

	/*
	ClassDB::bind_method(D_METHOD("set_attributes_add", "p_attributes_add"), &Ability::set_attributes_add);
	ClassDB::bind_method(D_METHOD("get_attributes_add"), &Ability::get_attributes_add);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes_add", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes_add", "get_attributes_add");

	ClassDB::bind_method(D_METHOD("set_attributes_remove", "p_attributes_remove"), &Ability::set_attributes_remove);
	ClassDB::bind_method(D_METHOD("get_attributes_remove"), &Ability::get_attributes_remove);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes_remove", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Attribute"), "set_attributes_remove", "get_attributes_remove");
	*/

	ClassDB::bind_method(D_METHOD("set_tags_required", "tags_required"), &Ability::set_tags_required);
	ClassDB::bind_method(D_METHOD("get_tags_required"), &Ability::get_tags_required);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_required", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_required", "get_tags_required" );

	ClassDB::bind_method(D_METHOD("set_tags_forbidden", "tags_forbidden"), &Ability::set_tags_forbidden);
	ClassDB::bind_method(D_METHOD("get_tags_forbidden"), &Ability::get_tags_forbidden);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_forbidden", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_forbidden", "get_tags_forbidden" );

	//PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Image")

	ClassDB::bind_method(D_METHOD("set_ability_name", "ability_name"), &Ability::set_ability_name);
	ClassDB::bind_method(D_METHOD("get_ability_name"), &Ability::get_ability_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "ability_name"), "set_ability_name", "get_ability_name");

	ClassDB::bind_method(D_METHOD("set_attribute_val", "attribute_name", "value"), &Ability::set_attribute_val);
}

void Effect::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_tags_add", "tags_add"), &Effect::set_tags_add);
	ClassDB::bind_method(D_METHOD("get_tags_add"), &Effect::get_tags_add);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_add", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_add", "get_tags_add");

	ClassDB::bind_method(D_METHOD("set_tags_remove", "tags_remove"), &Effect::set_tags_remove);
	ClassDB::bind_method(D_METHOD("get_tags_remove"), &Effect::get_tags_remove);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "tags_remove", PROPERTY_HINT_ARRAY_TYPE, "StringName"), "set_tags_remove", "get_tags_remove");

	ClassDB::bind_method(D_METHOD("set_commands", "tags_remove"), &Effect::set_commands);
	ClassDB::bind_method(D_METHOD("get_commands"), &Effect::get_commands);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "commands", PROPERTY_HINT_ARRAY_TYPE, "String"), "set_commands", "get_commands");

	ClassDB::bind_method(D_METHOD("set_duration", "duration"), &Effect::set_duration);
	ClassDB::bind_method(D_METHOD("get_duration"), &Effect::get_duration);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "duration"), "set_duration", "get_duration");

	ClassDB::bind_method(D_METHOD("set_cooldown", "cooldown"), &Effect::set_cooldown);
	ClassDB::bind_method(D_METHOD("get_cooldown"), &Effect::get_cooldown);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "cooldown"), "set_cooldown", "get_cooldown");
}

/*
void Effect::attach_effect(Entity *target_entity) {
	target_entity->add_effect(this);
}

void Effect::detach_effect(Entity *target_entity) {
	target_entity->clear_effect(this);
}*/

/*
Effect::Effect() : duration(0), cooldown(0) {
}*/

/*
void ResourceEcs::_bind_methods() {
	//ClassDB::bind_method(D_METHOD("set_id", "p_id"), &ResourceEcs::set_id);
	//ClassDB::bind_method(D_METHOD("get_id"), &ResourceEcs::get_id);
	//ADD_PROPERTY(PropertyInfo(Variant::INT, "p_id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("set_name_var", "p_name"), &ResourceEcs::set_name_var);
	ClassDB::bind_method(D_METHOD("get_name_var"), &ResourceEcs::get_name_var);
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "name_var"), "set_name_var", "get_name_var");
}
*/
/*
void NodeECS::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_archetype", "p_archetype"), &NodeECS::set_archetype);
	ClassDB::bind_method(D_METHOD("get_archetype"), &NodeECS::get_archetype);
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, "archetype", godot::PROPERTY_HINT_RESOURCE_TYPE, "Archetype"), "set_archetype", "get_archetype");
	//ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "archetype", PROPERTY_HINT_TYPE_STRING, String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":Archetype"), "set_archetype", "get_archetype");
}
*/

/*
void Actor::_bind_methods() {
}
*/

void Ecs::_notification(int _what) {
	switch(_what) {
		case NOTIFICATION_READY:
			print("Ecs READY!! ", Ecs::get_singleton()->get_instance_id());
			//print("Ecs Ready ability register size : ", abilities.size());
			print("Ecs Ready2 ability register size : ", Ecs::get_singleton()->ability_register.size());
/*
			// initialize abilities
			for(int i=0; i<abilities.size();i++) {
				Ability* ability = cast_to<Ability>(abilities[i]);
				ability->initialize();
			}
*/

			if (!Engine::get_singleton()->is_editor_hint()) {
				set_physics_process(true);
				print("enabled physics process");
			}
			break;
		case NOTIFICATION_PHYSICS_PROCESS:
			print("PHYSICS_PROCESS!!");
			process_ecs();
			break;
	}
}

Ecs *Ecs::get_singleton() {
	if (!Ecs::singleton) {
        Ecs::singleton = memnew(Ecs); // Use Godot's memory allocation
    }
    return Ecs::singleton;
}

void Ecs::connect(SceneTree* scene_tree) {
	if (scene_tree) {
        Window* root = scene_tree->get_root();
        if (root) {
			this->set_physics_process(true);
			root->call_deferred("add_child", this);
        }
    }
}

void Ecs::process_ecs() {
	//print("process_ecs");
	//todo: maybe make this multithreaded and also the actual array and map operations like * / etc. or the operations in effects, however this is done
	//print("ability register size : ", ability_register.size());

	print("HERE1");
	print("ability register size : ", Ecs::get_singleton()->ability_register.size());
	print("HERE2");

	for(Ability* ability : Ecs::get_singleton()->ability_register) {
	/*
	for(int i=0;i<abilities.size();i++) {
		Ability* ability = cast_to<Ability>(abilities[i]);
	*/	
		print("PRocesing ", ability->get_ability_name());
		if(ability->get_is_enabled()) { 
			print("1");
			ability->update_entities_approved(); // filter out entities without the necessary tags
			print("2");
			ability->update(); // update approved entities
			print("3");
		}
	}
	print("HERE3");
}

int64_t Ecs::create_entity(Object *object) {
	return entity_register.insert(object->get_instance_id());
}

void Ecs::remove_entity(Object *object) {
	entity_register.remove(object->get_instance_id());
}

void Ecs::grant_abliity(Object *object, Ability *ability) {
	ability->entities_assigned.insert(object->get_instance_id());
}

void Ecs::revoke_ability(Object *object, Ability *ability) {
	ability->entities_assigned.remove(object->get_instance_id());
}

/**
 * add tag to entity, this adds the tag, entity pair to the tag_register
 */
void Ecs::tag_add(Object* object, StringName tag) {
	tag_register[tag.hash()].insert(object->get_instance_id());	// insert entity into register (this will insert the object id into the entities whether the key exists or not)
}

/**
 * remove tag from entity, removes tag, entity pair from tag register
 */
void Ecs::tag_remove(Object* object, StringName tag) {
	tag_register[tag.hash()].remove(object->get_instance_id());
	// remove the tag from tag register if it has no entities (this isn't really necessary but just to keep things tidy as tag_add adds tag keys to the register)
	if(tag_register[tag.hash()].empty()) { tag_register.erase(tag.hash()); }
}


/*
Entity* Ecs::create_entity(Object* object) {
	Entity* new_entity = memnew(Entity); // reserve memory
	new_entity->set_object(object);
	entity_register.insert(new_entity);
	return new_entity;
}

void Ecs::remove_entity(Entity* entity) {
	entity_register.remove(entity);
	memdelete(entity); // free memory
}

/* //todo: add
void Ecs::register_archetype(Object* object, const TypedArray<Attribute>& attributes) {
	print("creating..");
	print("obj class", object->get_class());
	print("attributes", attributes.size());
	Archetype* p_archetype = memnew(Archetype(object));
	int archetype_id = archetype_map.insert(p_archetype);
	p_archetype->id = archetype_id;
	for(int i; i < attributes.size(); i++) {
		auto attribute = cast_to<Attribute>(attributes[i]);
		p_archetype->attributes.insert(attribute->id);
	}
}
*/

/*
void Ecs::register_object(Object *object) {
	int object_id = object_map.insert(object);
	print("register_object");

	array<Attribute*> object_attributes;

	// get attributes for all archetype ids associated with this object
	array<int> archetype_ids;
	//todo:

	for(Attribute* attribute : object_attributes) {
		attribute->create_attribute_data_entry(); // creates an entry in the attribute for this object and assigns the default values.
	}
*/
	/*
	//todo:remove
	print("registering archetype and creating attributes");
	print("archetypes ", archetype_map.size());
	*/
	/*
	print("attributes ", attribute_map.size());
	print("abilities ", ability_map.size());
	print("objects ", object_map.size());
	*/
	/*
	print("comp map size B: ", attribute_map.size());
	print("ability map size B: ", ability_map.size());
	*/

	// add default value entry in each member attribute at index object_id
	



/*

	//todo: remove for loop need to do for one attribute at a time based on the specific archetype attributes.
	for(int i=0;i<attribute_map.size();i++)
	{
		print("in for loop ", i);

		Attribute* attribute = attribute_map[i];
		//Variant data_var = attribute->get_data_var();
		/*
		attribute->values[object_id] = data_var;
		print("inserted ", object_id, " : ", data_var);
		//attribute->create_array_from_variant(attribute->get_data_var());
		*/
		/*
		int id;
		print("data type", attribute->data_var.get_type());
		switch(attribute->data_var.get_type()) {
			case Variant::BOOL:
				print("Vbool");
				attribute->data_array = sly::array<bool>();
				std::get<array<bool>>(attribute->data_array).insert(attribute->data_var);
				break;
			case Variant::INT:
				print("Vint");
				attribute->data_array = sly::array<int>();
				std::get<array<int>>(attribute->data_array).insert(attribute->data_var);
				break;
			case Variant::FLOAT:
				print("Vfloat");
				attribute->data_array = sly::array<float>();
				id = std::get<array<float>>(attribute->data_array).insert(attribute->data_var);
				print("inserted ", id, " into float attribute with value ", std::get<array<float>>(attribute->data_array)[id]);
				//array<float>* float_array = &std::get<array<float>>(attribute->data_array);
				//float_array->insert(attribute->data_var);
				break;
			case Variant::STRING:
				print("Vstring");
				attribute->data_array = sly::array<String>();
				std::get<array<String>>(attribute->data_array).insert(attribute->data_var);
				break;
			case Variant::STRING_NAME:
				print("Vstringname");
				attribute->data_array = sly::array<StringName>();
				std::get<array<StringName>>(attribute->data_array).insert(attribute->data_var);
				break;
				//todo: add other cases for primitive types
			default:
				print("Vvariant");
				attribute->data_array = sly::array<Variant>();
				std::get<array<Variant>>(attribute->data_array).insert(attribute->data_var);
		}
		*/

		/*
		int data_id = 
		print("Object Id ", object_id, "Data Id ", data_id);
		print("VARIANT DATA : ", attribute->values[object_id]);
		*/
	//}
/*
	for(int i=0;i<attribute_map.size();i++) {
			Attribute* attribute = attribute_map[i];
			for(int i=0;i<attribute->values.size();i++) {
				//print("Variant Data");
				//print("VARIANT DATA : ", attribute->values[i]);
				print("VARIANT DATA : ", attribute->values[i]);
			}
	}
*/
/*
	for(int i=0;i<attribute_map.size();i++)
	{
		Attribute* attribute = attribute_map[i];
		print(attribute.get_data)
	}
*/
//}

//todo:remove if unused, seems unnecessary
void Attribute::create_attribute_data_entry(int entity_id) {

	print("create_attribute_data_entry()");

	int index;
	switch(data_var.get_type()) {
		case Variant::BOOL:
			create_default_entry<bool>(entity_id, attribute_data);
			break;
		case Variant::INT:
			create_default_entry<int64_t>(entity_id, attribute_data);
			break;
		case Variant::FLOAT:
			create_default_entry<float>(entity_id, attribute_data);
			//attribute_data->get_data<float>()->insert(data_var);
			break;
		case Variant::STRING:
			create_default_entry<String>(entity_id, attribute_data);
			//attribute_data->get_data<String>()->insert(data_var);
			break;
		case Variant::STRING_NAME:
			create_default_entry<StringName>(entity_id, attribute_data);
			//attribute_data->get_data<StringName>()->insert(data_var);
			break;
		//todo: add other cases for primitive types
		default:
			create_default_entry<Variant>(entity_id, attribute_data);
			//attribute_data->get_data<Variant>()->insert(data_var);
	}
}


/*
void Ecs::unregister_object(Object *object) {
	object_map.remove(object_map.find[object]);
}*/

/*
void Ecs::register_archetype(Archetype *archetype) {
	archetype_map.insert(archetype);
	//Archetype* p_archetype = memnew(Archetype(p_archetype));
	//int archetype_id = archetype_map.insert(archetype);
	//archetype->set_id(archetype_id);
}

void Ecs::unregister_archetype(Archetype *archetype) {
	archetype_map.remove(archetype_map.find[archetype]);
}

void Ecs::register_ability(Ability *ability) {
	ability_map.insert(ability);
}

void Ecs::unregister_ability(Ability *ability) {
	ability_map.remove(ability_map.find[ability]);
}

void Ecs::register_attribute(Attribute *attribute) {
	attribute_map.insert(attribute);
}

void Ecs::unregister_attribute(Attribute *attribute) {
	attribute_map.remove(attribute_map.find[attribute]);
}
*/


void Ability::update_entities_approved() {
	// set to entities_assigned
	print(ability_name," update_entities_approved() Assigned1 ", entities_assigned.size());
	print(ability_name," update_entities_approved() Assigned1 ", this->entities_assigned.size());
	entities_approved = entities_assigned;	// makes a copy of this 'cos need a copy, not a reference as this will be modified
	print("update_entities_approved() Approved1 ", entities_approved.size());
	// approve entities based on tags
	for(int i=0;i<tags_required.size();i++) {
		StringName tag = tags_required[i];
		map<int64_t> entities_assigned_to_tag = Ecs::get_singleton()->tag_register[tag.hash()];
		entities_approved.intersect(entities_assigned_to_tag);
	}
	print("update_entities_approved() Assigned2 ", entities_assigned.size());
	print("update_entities_approved() Approved2 ", entities_approved.size());
}

void Ability::update() {
	print("updating ability ", get_ability_name());
	/*
	print("updating ability : ", Ecs::ability_map.find[this]);

	for(Ability* ability : Ecs::ability_map.value) {

	}*/

	//vector<Archetype*> affected_archetypes;
	//get_affected_archetypes()

	/*
	for (NodeEcs* node_ecs : node_ecs_map) {

	}*/

	GDVIRTUAL_CALL(_update);
}
/*
// loads callables from gdscript
void Ability::load_callable_script() {
	Ref<Script> script = ResourceLoader::get_singleton()->load("res://abilities.gd");
	if (script.is_valid()) {
		//Variant result = script->call("your_static_function", arguments);
		// Process the result
	}
}

// loads callables from C++ ability
void Ability::load_callable() {
	TypedArray<Callable> callables;
	Callable movement_ability = Callable(this, "update");
	movement_ability.call();
}
*/

/*
void AbilityUpdaters::ability_movement() {
}*/

	//for(AbilityUpdater::ge)


/*
//TypedArray<Variant::Type> Attribute::create_typed_array_from_variant(const Variant& p_variant) {
Array Attribute::create_array_from_variant(const Variant& p_variant) {
    // get the type from the Variant
    Variant::Type type = p_variant.get_type();

	//TypedArray<type> typed_node_array;
	//godot::Array new_array(base_array, godot::Variant::NIL, godot::StringName(), (godot::Script*)nullptr);
	//Array base_array; // Create an empty base array

	Array base_array;
	//TypedArray<Variant> base_array;

	StringName class_name = "";

	// If the variant holds an Object-derived type, we need its class name
    if (type == Variant::Type::OBJECT) {
        // We attempt to get the object's actual class name if it exists.
        // If p_variant is null/empty, we can't reliably get the class, 
        // so you might want a default behavior (e.g., untyped Array or Array[Object]).

		Object* object = cast_to<Object>(p_variant);
        if (object != nullptr) {
            Object* obj = p_variant.operator Object *();
            if (obj) {
                class_name = obj->get_class();
            }
        }
    }

    // 2. Create the TypedArray using the type information
    // The Array constructor allows setting the expected type at runtime.
    // We use the base Array constructor for runtime typing, then cast to TypedArray<Variant>.
    // Internally, Godot manages type checking for these arrays.

    Array new_array(base_array, type, class_name, (Script*)nullptr); // Pass type, class_name, and script (null for C++ built-ins)

	new_array.set_typed(type, Node::get_class_static(), Variant());

	new_array.push_back(p_variant);

	print("array created", new_array.size());
	print("variant value is :", p_variant);

    // Note: The TypedArray<T> C++ wrapper is mostly for compile-time convenience and
    // better C++ type handling, but the underlying Godot Array can have its type
    // set at runtime using the Variant::Type enum and class name.

    // You can now add elements of the correct type to the 'new_array'.
    // The Godot runtime will enforce the type check.
    // For this example, we return a TypedArray<Variant> which holds the runtime type info.
    // When passed to GDScript, it will behave as a typed array of the specified type.
    return new_array;
}
*/

void Ability::set_is_enabled(bool p_is_enabled) {
	/*
	if(p_is_enabled) {
		Ecs::get_singleton()->ability_register.insert(this);
		//print("Ability registered");
	} else {
		Ecs::get_singleton()->ability_register.remove(this);
		//print("Ability unregistered");
	}
	*/
	is_enabled = p_is_enabled;
}

bool Ability::get_is_enabled() {
	return is_enabled;
}

#if 0
void Entity::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_ability", "ability"), &Entity::add_ability);
	ClassDB::bind_method(D_METHOD("clear_ability", "ability"), &Entity::clear_ability);

	ClassDB::bind_method(D_METHOD("add_effect", "effect"), &Entity::add_effect);
	ClassDB::bind_method(D_METHOD("clear_effect", "effect"), &Entity::clear_effect);

	ClassDB::bind_method(D_METHOD("add_tag", "tag"), &Entity::add_tag);
	ClassDB::bind_method(D_METHOD("clear_tag", "tag"), &Entity::clear_tag);

	void add_ability();
	void clear_ability(Ability* p_ability);

	void add_effect(Effect* p_effect);
	void clear_effect(Effect* p_effect);

	void add_tag(StringName p_tag);
	void clear_tag(StringName p_tag);
}

void Entity::add_ability(Ability *p_ability) {
	abilities.insert(p_ability);
}

void Entity::clear_ability(Ability* p_ability) {
	abilities.remove(p_ability);
}

void Entity::add_effect(Effect *p_effect) {
	effects.insert(p_effect);
}

void Entity::clear_effect(Effect *p_effect) {
	effects.remove(p_effect);
}

void Entity::add_tag(StringName p_tag) {
	tags.insert(p_tag);
}

void Entity::clear_tag(StringName p_tag) {
	tags.remove(p_tag);
}

// set game object id from instance id
void Entity::set_object(Object* object) {
	object_id = object->get_instance_id();
}

// get game object ref from instance id
Object* Entity::get_object() {
	return UtilityFunctions::instance_from_id(object_id);
}
#endif

} // namespace sly