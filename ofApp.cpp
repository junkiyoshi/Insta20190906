#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(60);
	ofNoFill();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int len = 120;
	int param_step = 1;
	for (int x = len * 0.5; x <= ofGetWidth() - len * 0.5; x += len) {

		for (int y = len * 0.5; y <= ofGetHeight() - len * 0.5; y += len) {

			ofPushMatrix();
			ofTranslate(x, y);

			auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
			auto angle_x = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.0008), 0, 1, -PI, PI);
			auto angle_y = ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.0008), 0, 1, -PI, PI);
			auto angle_z = ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * 0.0008), 0, 1, -PI, PI);

			for (int param = 0; param < 100; param += param_step) {

				vector<glm::vec3> vertices = {
					glm::vec3(this->make_point(len, param), 0),
					glm::vec3(this->make_point(len, param + param_step), 0),
					glm::vec3(this->make_point(len * 0.45, param + param_step), 0),
					glm::vec3(this->make_point(len * 0.45, param), 0),
				};

				auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));
				vertices[2] = glm::vec4(vertices[2], 0) * rotation_z * rotation_y * rotation_x;
				vertices[3] = glm::vec4(vertices[3], 0) * rotation_z * rotation_y * rotation_x;

				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}