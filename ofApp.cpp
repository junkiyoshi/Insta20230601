#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	float span = 1;
	ofColor color;
	for (float y = 30; y < ofGetWindowHeight() - 30; y += span) {

		this->mesh.addVertex(glm::vec3(30, y, 0));
		this->mesh.addVertex(glm::vec3(ofGetWindowWidth() - 30, y, 0));
		this->mesh.addVertex(glm::vec3(ofGetWindowWidth() - 30, y + span, 0));
		this->mesh.addVertex(glm::vec3(30, y + span, 0));

		for (int i = this->mesh.getNumVertices() - 4; i < this->mesh.getNumVertices(); i++) {

			auto noise_value = ofMap(ofNoise(this->mesh.getVertex(i).y * 0.002, ofGetFrameNum() * 0.005), 0, 1, 0, 5);
			int int_noise_value = noise_value;
			float param = noise_value - int_noise_value;
			param = abs(param - 0.5);

			color.setHsb(ofMap(int_noise_value, 0, 5, 0, 255), 200, 255, ofMap(param, 0, 0.5, 255, 32));
			this->mesh.addColor(color);
		}

		this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
		this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 3); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}