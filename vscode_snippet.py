import json
from pathlib import Path


def create_snippets(source_dir: Path, out_file: Path, extension: str, scope: str):
    out = {}
    for cpp in source_dir.glob(f"*.{extension}"):
        lines = list(l.rstrip() for l in open(cpp))
        name = cpp.name
        out[name] = {
            "prefix": name,
            "scope": scope,
            "body": lines,
            "description": str(cpp),
        }

    with open(out_file, "w") as f:
        json.dump(out, f, indent=4)


if __name__ == "__main__":
    create_snippets(Path("./cpp"), Path(".vscode/cpp.code-snippets"), "cpp", "cpp")