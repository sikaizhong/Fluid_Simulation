#include<renderer/renderer.h>
namespace FS {
	RendererAPI Renderer::api;
	Light Renderer::light_;

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RendererAPI::SetViewport(0, 0, width, height);
	 }
	void Renderer::Init() {
		RendererAPI::Init();
	 }

	void Renderer::LoadFragmentShader(GLSLShader*&fs, std::string& filename) {
		RendererAPI::LoadFragmentShader(fs, filename);
	}
	void Renderer::LoadVertexShader(GLSLShader*&vs, std::string& filename) {
		RendererAPI::LoadVertexShader(vs, filename);
	}
	void Renderer::CreateProgram(GLSLProgram*& program, GLSLShader*&vs, GLSLShader*&fs, std::string& vsf, std::string& fgs) {
		RendererAPI::LoadVertexShader(vs, vsf);
		RendererAPI::LoadFragmentShader(fs, fgs);
		RendererAPI::InitProgram(program, vs, fs);
	}

	void Renderer::LoadXYZMesh(std::string& folderName) {
		RendererAPI::LoadXYZMesh(folderName);
	}

	void Renderer::DrawXYZMesh(int frame) {
		RendererAPI::DrawXYZMesh(frame);
	}
	void Renderer::linkMVP(GLSLProgram* program, glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
		RendererAPI::linkMVP(program, model, view, projection);

	}

	void Renderer::useProgram(GLSLProgram* program) {
		RendererAPI::useProgram(program);
	}




	/*void Renderer::LoadTriangularMesh(Mesh* mesh) {
		api.loadTriangularMesh(mesh);
	}
	void Renderer::LoadTetrahedronMesh(Mesh* mesh) {
		api.loadTetraHedronMesh(mesh);

	}



	void Renderer::DrawTriangularMesh(Mesh*mesh) {
		//RendererAPI::loadTriangularMesh(mesh);// TODO
		int count = 0;
		if (!mesh->hasCells)
		count = mesh->face_.size();
		else
		count = mesh->cell_.size() / 4 * 4 * 3;
		//std::cout << "count: " << count / 12 << std::endl;
		RendererAPI::DrawTriangularMesh(count);
	}

	void Renderer::DrawTriangularMesh_draw_by_point(Mesh*mesh) {
		int count = 0;
		//if (mesh->hasCells)
		//	count = mesh->cell_.size();
		//else
		//	count = mesh->face_.size();
		count = mesh->face_.size()/3;
		//std::cout << "count: " << count << std::endl;
		RendererAPI::DrawTriangularMesh_draw_by_point(count);

	}



	
	void Renderer::DrawWireFrame(Mesh*mesh) {
		int count = 0;
		if (!mesh->hasCells)
			count = mesh->face_.size();
		else
			count = mesh->cell_.size() / 4 * 4 * 3;
		RendererAPI::DrawWireFrame(count);

	}



	void Renderer::DrawVertices(Mesh*mesh) {
		//RendererAPI::loadTriangularMesh(mesh);// TODO
		unsigned int count = mesh->vertex_.size()/3;
		RendererAPI::DrawVertices(count);
	}


	void Renderer::DrawCurvedMesh() {
		RendererAPI::DrawCurvedMesh();
	}

	void Renderer::DrawClippingPlane() {
		RendererAPI::DrawClippingPlane();

	}



	void Renderer::DrawPan() {
		RendererAPI::DrawPan();
	}

	

	void Renderer::CreateProgram(GLSLProgram*& program, GLSLShader*&vs, GLSLShader*&gs, GLSLShader*&fs, std::string& vsf, std::string& gsf, std::string& fgf) {
		RendererAPI::LoadVertexShader(vs, vsf);
		RendererAPI::LoadGeometryShader(gs, gsf);
		RendererAPI::LoadFragmentShader(fs, fgf);
		RendererAPI::InitProgram(program, vs,gs, fs);
	}


	void Renderer::CreateComputeProgram(GLSLProgram*& program, GLSLShader*&cs, std::string& csf) {
		RendererAPI::LoadComputeShader(cs, csf);
		RendererAPI::InitComputeProgram(program, cs);
	}


	




	void Renderer::linkMVP(GLSLProgram* program,glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
		RendererAPI::linkMVP(program,model, view, projection);

	}

	void Renderer::useProgram(GLSLProgram* program) {
		RendererAPI::useProgram(program);
	}

	


	void Renderer::removeProgram() {
		RendererAPI::removeProgram();
	}
	void Renderer::setPointSize(float val) {
		RendererAPI::setPointSize(val);
	}
	void Renderer::setEdgeWidth(float val) {
		RendererAPI::setEdgeWidth(val);
	}

	void Renderer::configLight(GLSLProgram* program,Light&light) {
		RendererAPI::configLight(program, light);
	 }
	void Renderer::configClippingPlane(GLSLProgram* program, ClippingPlane& clippingPlane) {
		RendererAPI::configClippingPlane(program, clippingPlane);
	}


	void Renderer::configClippingPlane(GLSLProgram*program, GLSLShader*&shader, ClippingPlane&clippingPlane) {
		RendererAPI::configClippingPlane(program,shader, clippingPlane);

	}
	*/


}