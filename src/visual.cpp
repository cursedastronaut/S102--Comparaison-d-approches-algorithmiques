#include "visual.h"

VisualIDK::VisualIDK() {
}

void VisualIDK::Update() {
	if (!dontRefresh) {
		post = original;
	} else {
		noirBlanc = false;
		composantRouge = false;
		niveauxGris = false;
		luminosity = false;
		contraste = false;
		rotationD = false;
	}
	if (noirBlanc)
		post = post.noirEtBlanc();
	if (composantRouge)
		post = post.composanteRouge();
	if (niveauxGris)
		post = post.niveauxGris();
	if (luminosity)
		post = post.changeLuminosity(luminosityF);
	if (contraste)
		post = post.changeContraste(contrasteF);
	if (rotationD)
		post = post.rotationD();
	if (rotationG)
		post = post.rotationG();
	if (retournementH)
		post = post.retournementH();
	if (retournementV)
		post = post.retournementV();
	if (rognerD)
		post = post.rognerD();
}

void VisualIDK::Draw() {
	for (uint32_t y = 0; y < post.getHauteur(); ++y) {
		for (uint32_t x = 0; x < post.getLongueur(); ++x) {
			dl->AddRectFilled({x*pixelSize,y*pixelSize}, {x*pixelSize+pixelSize, y*pixelSize+pixelSize},
			IM_COL32(post.img.red[x][y], post.img.green[x][y], post.img.blue[x][y], 255));
		}
	}
}

void VisualIDK::UI() {
	ImGui::Begin("Debug");
	ImGui::Checkbox("Noir & Blanc", &noirBlanc);
	ImGui::Checkbox("Composante Rouge", &composantRouge);
	ImGui::Checkbox("Niveaux Gris", &niveauxGris);
	ImGui::Checkbox("Luminosité", &luminosity);
	ImGui::InputFloat("l", &luminosityF, 0.1f, 0.2f);
	ImGui::Checkbox("Contraste", &contraste);
	ImGui::InputFloat("c", &contrasteF, 0.1f, 0.2f);
	ImGui::Checkbox("Rotation Droite", &rotationD);
	ImGui::Checkbox("Rotation Gauche", &rotationG);
	ImGui::Checkbox("Retournement Horizontal", &retournementH);
	ImGui::Checkbox("Retournement Vertical", &retournementV);
	ImGui::Checkbox("Rognement Droite", &rognerD);
	ImGui::Checkbox("No Refresh", &dontRefresh);
	ImGui::NewLine();
	ImGui::InputText("File", fileTempBuffer, 50);
	if (ImGui::Button("Charger", {64, 32}))
		original = Image(fileTempBuffer);
	ImGui::InputInt("Pixel Size", &pixelSize, 1, 2);
	if (ImGui::Button("Écrire", {64, 32})) {
		post.ecrire();
		std::cout << "Ecriture terminee" << std::endl;
	}
	ImGui::End();
}