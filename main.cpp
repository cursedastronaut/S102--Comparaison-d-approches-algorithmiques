#include "menu_files.hpp"

int main(int argc, char* argv[]) {
	Image image = Image("ppm_tests/Flowerbed-large.ppm");
	image.niveauxGris().ecrire("Couleur_GENERATED.ppm");
	return 0;
}