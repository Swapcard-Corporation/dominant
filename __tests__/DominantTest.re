Jest.describe("Pixel.ofCharArray", () => {
  Jest.test("an empty array should return an empty list", () =>
    Jest.ExpectJs.expect(Dominant.ofFloatArray([||]))
    |> Jest.ExpectJs.toEqual([||])
  );
  Jest.test("a partial array should return an empty list", () =>
    Jest.ExpectJs.expect(Dominant.ofFloatArray([|1.|]))
    |> Jest.ExpectJs.toEqual([||])
  );
  Jest.test("a 4 char array should return a unique pixel list", () =>
    Jest.Expect.expect(Dominant.ofFloatArray([|1., 1., 1., 1.|]))
    |> Jest.Expect.toEqual([|Dominant.ofColor(1., 1., 1., 1.)|])
  );
  Jest.test("a 5 char array should return a unique pixel list", () =>
    Jest.Expect.expect(Dominant.ofFloatArray([|1., 1., 1., 1., 1.|]))
    |> Jest.Expect.toEqual([|Dominant.ofColor(1., 1., 1., 1.)|])
  );
  Jest.test("a 8 char array should return a 2 pixel list", () =>
    Jest.Expect.expect(
      Dominant.ofFloatArray([|1., 1., 1., 1., 1., 1., 1., 1., 1.|])
    )
    |> Jest.Expect.toEqual([|
         Dominant.ofColor(1., 1., 1., 1.),
         Dominant.ofColor(1., 1., 1., 1.)
       |])
  );
});

Jest.describe("Pixel.bucket", () =>
  Jest.test("return main colors", () => {
    let pixelA = Dominant.ofColor(50., 50., 50., 1.);
    let pixelB = Dominant.ofColor(40., 40., 40., 1.);
    let pixelC = Dominant.ofColor(80., 80., 50., 1.);
    let pixelD = Dominant.ofColor(148., 148., 148., 1.);
    let pixelArray = [|pixelA, pixelB, pixelC, pixelD|];
    Jest.Expect.expect(Dominant.paletteOfPixelArray(pixelArray, ~square=1, ()))
    |> Jest.Expect.toEqual([|
         Dominant.ofColor(
           45.27692569068709,
           45.27692569068709,
           45.27692569068709,
           1.
         ),
         Dominant.ofColor(
           118.96217886370441,
           118.96217886370441,
           110.46266337545913,
           1.
         )
       |]);
  })
);