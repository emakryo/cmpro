import json
from pathlib import Path


def create_snippets(source_dir: Path, out_file: Path, extension: str):
    out = {}
    for cpp in source_dir.glob(f"*.{extension}"):
        lines = list(l.rstrip() for l in open(cpp))
        name = cpp.name
        out[name] = {
            "prefix": name,
            "body": lines,
            "description": str(cpp),
        }

    with open(out_file, "w") as f:
        json.dump(out, f, indent=4)


if __name__ == "__main__":
    output = Path("./snippets")
    output.mkdir(parents=True, exist_ok=True)

    create_snippets(Path("./cpp"), output / "cpp.json", "cpp")