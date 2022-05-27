
class Renderer : public Object {
public:

	//Material* GetMaterial() {
	//	typedef Material* (*Renderer_GetMaterial_t)(Renderer* this_);
	//	return Function<Renderer_GetMaterial_t>("UnityEngine.CoreModule", "UnityEngine", "Renderer", "GetMaterial", 0)(this);
	//}

	Array<Material*>* GetMaterials() {
		typedef Array<Material*>* (*Renderer_GetMaterialArray_t)(Renderer* this_);
		return Function<Renderer_GetMaterialArray_t>("UnityEngine.CoreModule", "UnityEngine", "Renderer", "GetMaterialArray", 0)(this);
	}
};