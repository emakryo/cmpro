import json
import re
from pathlib import Path


def create_snippets(source_dir: Path, out_file: Path, extension: str, scope: str):
    out = {}
    for fname in source_dir.glob(f"*.{extension}"):
        lines = list(l.rstrip() for l in open(fname))
        name = fname.name
        out[name] = {
            "prefix": name,
            "scope": scope,
            "body": lines,
            "description": str(fname),
        }

    # NB cannot nest for now
    match = re.compile(r"#include\"(.*)\"")
    for name, body in out.items():
        for i, line in enumerate(body["body"]):
            m = match.fullmatch(line)
            if m is None:
                 continue

            fname = m[1]
            body["body"][i:i+1] = out[fname]["body"]


    with open(out_file, "w") as f:
        json.dump(out, f, indent=4)


if __name__ == "__main__":
    create_snippets(Path("./cpp"), Path(".vscode/cpp.code-snippets"), "cpp", "cpp")