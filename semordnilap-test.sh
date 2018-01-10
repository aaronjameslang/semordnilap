#! /bin/sh
set -eu

it_passes_stressed() {
  out="$(./semordnilap stressed)"
  exit_code="$?"
  test "$out" = 'stressed -> desserts'
  test "$exit_code" -eq 0
}

it_passes_desserts() {
  out="$(./semordnilap desserts)"
  exit_code="$?"
  test "$out" = 'desserts -> stressed'
  test "$exit_code" -eq 0
}

it_passes_elppa() {
  out="$(./semordnilap elppa)"
  exit_code="$?"
  test "$out" = 'elppa -> apple'
  test "$exit_code" -eq 0
}

it_fails_apple() {
  exit_code=0
  out="$(./semordnilap apple)" || exit_code="$?"
  test "$out" = 'apple -> elppa'
  test "$exit_code" -eq 1
}
