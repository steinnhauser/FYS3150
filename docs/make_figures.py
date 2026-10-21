"""Build the README figures in docs/assets/ from data stored in this repository.

Run from the repository root:

    uv run --with matplotlib --with numpy --with h5py --with pillow python docs/make_figures.py

- heat-diffusion.gif      fys3150/Project5/twodim.gif, cropped and shortened
- space-weather-2007.png  swss-boston-2018/Project_ACE-STB/*.txt (NOAA data)
- plasma-potential.png    4dsnw-kobe-2019/Kobe/Run_{6,7,9}/phisp00_0000.h5
"""

import datetime as dt
import pathlib
import re

import h5py
import matplotlib

matplotlib.use("Agg")
import matplotlib.dates as mdates
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.colors import SymLogNorm
from PIL import Image

ROOT = pathlib.Path(__file__).resolve().parent.parent
OUT = ROOT / "docs" / "assets"
INK, MUTED, GRID = "#14243a", "#5c667a", "#e3e8ef"

plt.rcParams.update({
    "font.size": 10,
    "axes.edgecolor": MUTED,
    "axes.labelcolor": INK,
    "axes.titlecolor": INK,
    "axes.titleweight": "bold",
    "axes.spines.top": False,
    "axes.spines.right": False,
    "axes.grid": True,
    "grid.color": GRID,
    "xtick.color": MUTED,
    "ytick.color": MUTED,
})


def heat_diffusion() -> None:
    gif = Image.open(ROOT / "fys3150/Project5/twodim.gif")
    frames = []
    for i in range(0, gif.n_frames, 8):
        gif.seek(i)
        frame = gif.convert("RGB").crop((110, 62, 474, 426)).resize((260, 260), Image.LANCZOS)
        frames.append(frame.quantize(colors=64))
    frames[0].save(OUT / "heat-diffusion.gif", save_all=True, append_images=frames[1:],
                   duration=140, loop=0, optimize=True)


def read_noaa(name: str) -> tuple[list[dt.datetime], np.ndarray]:
    pattern = re.compile(r"^(\d\d-\d\d-\d{4}) (\d\d:\d\d):\S+\s+(-?[\d.eE+]+)\s*$")
    times, values = [], []
    for line in (ROOT / "swss-boston-2018/Project_ACE-STB" / name).read_text(encoding="latin-1").splitlines():
        if m := pattern.match(line):
            times.append(dt.datetime.strptime(f"{m[1]} {m[2]}", "%d-%m-%Y %H:%M"))
            value = float(m[3])
            values.append(value if abs(value) < 1e4 else np.nan)
    return times, np.array(values)


def space_weather() -> None:
    end = dt.datetime(2007, 9, 1)
    series = [
        ("ACE_data_2007_B.txt", "|B| [nT]", "Interplanetary magnetic field (ACE)", "#d99a1e"),
        ("DST_index_2007_jan_sep.txt", "Dst [nT]", "Geomagnetic storm index", "#e0566b"),
        ("Daily_Sunspots_20070101_20070901.txt", "count", "Daily sunspot number", "#3f6fb5"),
    ]
    fig, axes = plt.subplots(3, 1, figsize=(10, 5.6), sharex=True, layout="constrained")
    for ax, (name, unit, title, color) in zip(axes, series):
        t, v = read_noaa(name)
        keep = [i for i, x in enumerate(t) if x < end]
        t, v = [t[i] for i in keep], v[keep]
        ax.plot(t, v, color=color, linewidth=0.8)
        ax.fill_between(t, v, np.nanmin(v) if "Dst" not in unit else 0, color=color, alpha=0.12, linewidth=0)
        ax.set_ylabel(unit)
        ax.set_title(title, loc="left", fontsize=10)
    axes[-1].xaxis.set_major_formatter(mdates.DateFormatter("%b"))
    fig.suptitle("Solar wind and geomagnetic activity, January–August 2007", color=INK, fontweight="bold", x=0.01, ha="left")
    fig.savefig(OUT / "space-weather-2007.png", dpi=130)
    plt.close(fig)


def plasma_potential() -> None:
    runs = [("Run_6", "H⁺"), ("Run_7", "He⁺"), ("Run_9", "O⁺")]
    slices = []
    for run, _ in runs:
        with h5py.File(ROOT / "4dsnw-kobe-2019/Kobe" / run / "phisp00_0000.h5") as f:
            slices.append(f["phisp0000"][:, :, 64].T)
    limit = max(np.abs(s).max() for s in slices)
    norm = SymLogNorm(linthresh=5, vmin=-limit, vmax=limit, base=10)
    fig, axes = plt.subplots(1, 3, figsize=(10, 3.7), layout="constrained")
    for ax, s, (_, title) in zip(axes, slices, runs):
        image = ax.imshow(s, origin="lower", cmap="RdBu_r", norm=norm)
        ax.contour(s, levels=[-60, -40, -20, -5], colors=INK, linewidths=0.5, alpha=0.6)
        ax.set_title(f"{title} ions · floating potential {s.min():.0f}", fontsize=10)
        ax.set_axis_off()
    bar = fig.colorbar(image, ax=axes, shrink=0.85, label="potential (simulation units)")
    bar.set_ticks([-100, -10, 0, 10, 100, 500])
    bar.set_ticklabels(["−100", "−10", "0", "10", "100", "500"])
    fig.suptitle("Particle-in-cell: potential around a spacecraft with biased Langmuir probes", color=INK, fontweight="bold", x=0.01, ha="left")
    fig.savefig(OUT / "plasma-potential.png", dpi=130)
    plt.close(fig)


if __name__ == "__main__":
    OUT.mkdir(parents=True, exist_ok=True)
    heat_diffusion()
    space_weather()
    plasma_potential()
    for path in sorted(OUT.iterdir()):
        print(f"{path.relative_to(ROOT)}: {path.stat().st_size // 1024} KB")
