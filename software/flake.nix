{
  description = "Pilkki: SWD flashing tool for EFM32 microcontrollers";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";

    src = {
      url = "file:..?ref=main";
      type = "git";
      submodules = true;
      flake = false;
    };
  };

  outputs = { nixpkgs, flake-utils, src, ... }:
    let
      pilkki = pkgs:
        let
          argparse = pkgs.fetchFromGitHub {
            owner = "morrisfranken";
            repo = "argparse";
            rev = "5d3710809364e694f33243810bbd1345975ae1c3";
            sha256 = "sha256-YJ0kh1tOJgBfo3v3ZoMUlMpdj6Z2BAuOXWbl52Y2J3w=";
          };
          magic_enum = pkgs.fetchFromGitHub {
            owner = "Neargye";
            repo = "magic_enum";
            rev = "v0.9.3";
            sha256 = "sha256-Cf2m4rrJw8igzTM5W8HU5X5Eam1QMlarShPK0eY6NQ8=";
          };
        in
        with pkgs; stdenv.mkDerivation {
          name = "pilkki";
          src = "${src}/software";

          nativeBuildInputs = [ cmake ninja ];
          buildInputs = [ libudev-zero ];

          cmakeFlags = [
            "-DFETCHCONTENT_SOURCE_DIR_ARGPARSE=${argparse}"
            "-DFETCHCONTENT_SOURCE_DIR_MAGIC_ENUM=${magic_enum}"
          ];
        };
    in
    flake-utils.lib.eachDefaultSystem
      (system:
        {
          packages.default = pilkki nixpkgs.legacyPackages.${system};
        }
      ) // {
      overlays.default = _: prev: {
        pilkki = pilkki prev;
      };
    };
}
