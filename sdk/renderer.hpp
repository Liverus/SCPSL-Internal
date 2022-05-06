
class Renderer : public OBJECT {
public:

	//Material* GetMaterial() {
	//	typedef Material* (*Renderer_GetMaterial_t)(Renderer* this_);
	//	return Function<Renderer_GetMaterial_t>("UnityEngine.CoreModule", "UnityEngine", "Renderer", "GetMaterial", 0)(this);
	//}

	ARRAY<Material*>* GetMaterials() {
		typedef ARRAY<Material*>* (*Renderer_GetMaterialArray_t)(Renderer* this_);
		return Function<Renderer_GetMaterialArray_t>("UnityEngine.CoreModule", "UnityEngine", "Renderer", "GetMaterialArray", 0)(this);
	}
};