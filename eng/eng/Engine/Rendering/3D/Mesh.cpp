#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_) :  VA0(0), VB0(0), textureLoc(0)
{
	shaderProgram = shaderProgram_;
	submesh = subMesh_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	OnDestroy();
}

void Mesh::Render(Camera* camera, std::vector<glm::mat4> &instances)
{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, submesh.textureID);

	
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetVeiw()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPrespective()));
	
	glBindVertexArray(VA0);

	for (int i = 0; i < instances.size(); i++) {
		glUniformMatrix4fv(modleLoc, 1, GL_FALSE, glm::value_ptr(instances[i]));
		glDrawArrays(GL_TRIANGLES, 0, submesh.vertexList.size());
	}
	
	

	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::OnDestroy()
{
	glDeleteVertexArrays(1, &VA0);
	glDeleteBuffers(1, &VB0);

	submesh.vertexList.clear();
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VA0);
	glGenBuffers(1, &VB0);

	glBindVertexArray(VA0);
	glBindBuffer(GL_ARRAY_BUFFER, VB0);
	glBufferData(GL_ARRAY_BUFFER, submesh.vertexList.size() * sizeof(Vertex), &submesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));

	//NORMALS
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));


	//TEXTURE COORDINATES
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	//TEXTURE COORDINATES
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modleLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

}
