#include<renderer/rendererapi.h>

namespace turbo {


	void RendererAPI::loadTetraHedronMesh_draw_by_point(Mesh* mesh) {

		getComputeShaderData(mesh);
		unsigned int numFacets = mesh->cell_.size();// face is duplicated;
		// vertex will have all three vertices of a triangle;
		float* vertex = new float[numFacets * 9];
		unsigned int index[4][3] = { 0,1,2,0,1,3,0,2,3,1,2,3 };

		for (int i = 0; i < mesh->cell_.size() / 4; i++) {
			for (int j = 0; j < 4; j++) {
				int index1 = index[j][0];
				int index2 = index[j][1];
				int index3 = index[j][2];
				vertex[36 * i + 9 * j + 0] = mesh->vertex_[3*mesh->cell_[4*i+index1]];
				vertex[36 * i + 9 * j + 1] = mesh->vertex_[3 * mesh->cell_[4 * i + index1]+1];
				vertex[36 * i + 9 * j + 2] = mesh->vertex_[3 * mesh->cell_[4 * i + index1]+2];

				vertex[36 * i + 9 * j + 3] = mesh->vertex_[3 * mesh->cell_[4 * i + index2]];
				vertex[36 * i + 9 * j + 4] = mesh->vertex_[3 * mesh->cell_[4 * i + index2]+1];
				vertex[36 * i + 9 * j + 5] = mesh->vertex_[3 * mesh->cell_[4 * i + index2]+2];

				vertex[36 * i + 9 * j + 6] = mesh->vertex_[3 * mesh->cell_[4 * i + index3]];
				vertex[36 * i + 9 * j + 7] = mesh->vertex_[3 * mesh->cell_[4 * i + index3]+1];
				vertex[36 * i + 9 * j + 8] = mesh->vertex_[3 * mesh->cell_[4 * i + index3]+2];
			}
		}

		if (glIsVertexArray(m_VertexArray))
			glDeleteVertexArrays(1, &m_VertexArray);
		if (glIsVertexArray(m_VertexArray_Point))
			glDeleteVertexArrays(1, &m_VertexArray_Point);


		glDeleteBuffers(1, &m_VertexBuffer); // no side effect;
		glDeleteBuffers(1, &m_IndexBuffer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*numFacets*9,vertex, GL_STATIC_DRAW);
		
		glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
		



		glBindBuffer(GL_ARRAY_BUFFER, faceVisibilityBuffer);
		glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, 0, (void*)0);


		//glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3); // token

		glEnableVertexAttribArray(7);

		glBindVertexArray(0);

		






	}




	void RendererAPI::getComputeShaderData_draw_by_point(Mesh* mesh) {




	}


	void RendererAPI::DrawTriangularMesh_draw_by_point(int count) {

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glBindVertexArray(m_VertexArray);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glDrawArrays(GL_POINTS, 0, count);
		glBindVertexArray(0);
		glDisable(GL_POLYGON_OFFSET_FILL);



	}



};
