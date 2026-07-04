# archcheck — new-clone drift, live demo

> **The 30-second story:** you open a PR. Somewhere in the diff you pasted a function
> instead of calling it. Before a human even looks, [archcheck](https://github.com/blurman-ai/archcheck)
> leaves a warning **on that exact line**: *"copy-paste introduced (EXACT): clone of `seed/widgets.c`."*
> It doesn't block you (it's advisory) — it just makes the copy-paste impossible to miss.

This repo is a real C codebase ([monit](https://mmonit.com/monit/), a process-monitoring
daemon) with one **demo workflow** wired in: [`.github/workflows/archcheck-pr.yml`](.github/workflows/archcheck-pr.yml).
On every PR it runs `archcheck --diff` and surfaces the **`DRIFT.NEW_CLONE`** advisory on three channels:

| Channel | Where you see it |
|---|---|
| **Inline annotation** | a `::warning::` on the exact copy-pasted line, in the PR **Files changed** tab |
| **Sticky comment** | one summary comment in the PR **conversation**, updated in place |
| **Step summary** | the full `--diff` report, one click from the run page |

There is **no red ❌** — `DRIFT.NEW_CLONE` is advisory (exit 0). The check stays green; the
warning is informational. (Turning copy-paste into a hard gate is a later opt-in.)

## The demo PRs

Each branch is one PR. Nine **fire** the advisory (real copy-paste — exact, whole-file,
renamed, and **partial/structural** copies where only part of the code matches) and five stay
**silent** (they look like copy-paste to a naive tool but aren't). The negatives are the whole
point — they're the false-positive classes the detector is built to *not* trip on. The `s*` cases
are Type-3 (near-miss) clones: the copy has an inserted line, a changed token, or extra
trailing logic, and archcheck still flags it as `STRUCTURAL`.

| PR (branch) | What it does | Surface |
|---|---|---|
| `p1-copy-func-into-existing-file` | pastes a function into an existing file | 🟡 fires |
| `p2-whole-file-copy` | copies a whole file | 🟡 fires |
| `p3-large-block-copy` | pastes a large multi-function block | 🟡 fires |
| `p4-exact-copy` | exact copy of a function elsewhere | 🟡 fires |
| `p5-renamed-copy` | copy with a moderate rename (Type-2 clone) | 🟡 fires |
| `s1-partial-insert-midbody` | copy with **one statement inserted** mid-body (Type-3) | 🟡 fires (STRUCTURAL) |
| `s2-partial-inserted-block` | copy with **a 3-line block inserted** (Type-3) | 🟡 fires (STRUCTURAL) |
| `s3-partial-one-token-changed` | near-identical copy, **one operator changed** | 🟡 fires (STRUCTURAL) |
| `s4-partial-trailing-added` | copy with **extra trailing logic** appended | 🟡 fires (STRUCTURAL) |
| `n1-unique-new-code` | genuinely new code | ✅ silent |
| `n2-move-no-copy` | **moves** code (delete here, add there) — not a copy | ✅ silent |
| `n3-below-threshold` | a dup too tiny to matter | ✅ silent |
| `n4-preexisting-clone-touched` | reformats a clone that **already existed** (parent-guard) | ✅ silent |
| `n5-formatting-only` | whitespace-only change | ✅ silent |

> Why the negatives stay silent: archcheck only flags clones **introduced by the diff**
> (intersecting the added lines), and a **parent-guard** drops any pair that was already a
> clone in the base — so reformatting pre-existing duplication never lights up.

## Screenshots

<!-- RUNBOOK step: drop the captured surfaces here and link them from the archcheck README. -->
- _Inline annotation on the pasted line:_ `docs/inline-annotation.png` _(TODO)_
- _Sticky PR comment:_ `docs/sticky-comment.png` _(TODO)_

## License

This demo bundles the **monit** source purely as a realistic sample codebase. monit is
GPL-licensed; see [`COPYING`](COPYING) / [`LICENSE`](LICENSE) and [`NOTICE`](NOTICE).
