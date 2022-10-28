use anyhow::{anyhow, Result};
use cargo_manifest::Manifest;
use std::{io::Read, path::PathBuf};
use structopt::StructOpt;

#[derive(StructOpt)]
enum Xtask {
    /// Create template.
    Template {
        /// Name of contest.
        name: String,
    },
    /// Compress Rust file
    Compress {
        /// Whther to apply rustfmt to output, default output is minified
        #[structopt(short, long)]
        format: bool,
    },
}

fn main() -> Result<()> {
    let opt = Xtask::from_args();

    match opt {
        Xtask::Template { name } => template(name),
        Xtask::Compress { format } => compress(format),
    }
}

fn template(name: String) -> Result<()> {
    let root_dir = PathBuf::from(std::env::var("CARGO_MANIFEST_DIR")?).join("..");
    let target_dir = root_dir.join(format!("src/{}", name));
    std::fs::create_dir_all(&target_dir)?;

    let manifest_template_path = root_dir.join("rs/Cargo.toml");
    let manifest_path = target_dir.join("Cargo.toml");
    if manifest_path.exists() {
        println!("Already exists {}", name);
    }
    let manifest = std::fs::read_to_string(&manifest_template_path)?;
    let manifest = manifest.replace(r#"name = "template""#, &format!(r#"name = "{}""#, name));

    std::fs::write(manifest_path, &manifest)?;

    let src_dir = target_dir.join("src/bin");
    let template_path = root_dir.join("rs/src/template.rs");
    std::fs::create_dir_all(&src_dir)?;
    for p in 'a'..='f' {
        std::fs::copy(&template_path, src_dir.join(format!("{}.rs", p)))?;
    }

    let workspace_manifest_path = root_dir.join("Cargo.toml");
    let mut workspace_manifest = Manifest::from_path(&workspace_manifest_path)?;
    let members = &mut workspace_manifest
        .workspace
        .as_mut()
        .ok_or_else(|| anyhow!("No workspace present."))?
        .members;

    let package = format!("src/{}", name);
    if !members.contains(&package) {
        members.push(package);
    }

    std::fs::write(
        workspace_manifest_path,
        taplo::formatter::format(
            &toml::to_string(&workspace_manifest)?,
            taplo::formatter::Options::default(),
        ),
    )?;
    Ok(())
}

fn compress(format: bool) -> Result<()> {
    let mut stdin = std::io::stdin().lock();
    let mut buf = String::new();
    stdin.read_to_string(&mut buf)?;

    let out = xtask::compress(&buf, format)?;

    println!("{}", out);

    Ok(())
}
