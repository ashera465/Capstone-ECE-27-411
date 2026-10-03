import numpy as np


def compute_stokes(I0, I45, I90, I135):

    # Convert camera data to floating point
    I0 = np.asarray(I0, dtype=np.float32)
    I45 = np.asarray(I45, dtype=np.float32)
    I90 = np.asarray(I90, dtype=np.float32)
    I135 = np.asarray(I135, dtype=np.float32)

    # Verify matching image dimensions
    if not (
        I0.shape == I45.shape
        == I90.shape == I135.shape
    ):
        raise ValueError(
            "Polarization images must have identical dimensions"
        )

    # Compute Stokes parameters
    S0 = I0 + I90
    S1 = I0 - I90
    S2 = I45 - I135

    # Calculate DoLP
    DoLP = np.zeros_like(S0)
    valid = S0 > 1e-8

    DoLP[valid] = (
        np.sqrt(S1[valid]**2 + S2[valid]**2)
        / S0[valid]
    )

    # Calculate AoLP
    AoLP = 0.5 * np.arctan2(S2, S1)
    AoLP = np.degrees(AoLP) % 180

    # Return results
    return {
        "S0": S0,
        "S1": S1,
        "S2": S2,
        "DoLP": DoLP,
        "AoLP": AoLP
    }
