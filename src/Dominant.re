type pixel = {
  red: float,
  green: float,
  blue: float
};

type range = {
  min: float,
  max: float
};

type colorRange = {
  red: range,
  green: range,
  blue: range
};

let reduceRange = (color, range) => {
  min: min(color, range.min),
  max: max(color, range.max)
};

let reduceColorRange = (pixel: pixel, ~ranges=?, ()) =>
  switch ranges {
  | None => {
      red: {
        min: pixel.red,
        max: pixel.red
      },
      green: {
        min: pixel.green,
        max: pixel.green
      },
      blue: {
        min: pixel.blue,
        max: pixel.blue
      }
    }
  | Some(ranges) => {
      red: reduceRange(pixel.red, ranges.red),
      green: reduceRange(pixel.green, ranges.green),
      blue: reduceRange(pixel.blue, ranges.blue)
    }
  };

let ofColor = (red, green, blue, _) : pixel => {red, green, blue};

let ofFloatArray = colorArray => {
  let rec _fromColorArray = (position, acc) =>
    if (position + 3 < Array.length(colorArray)) {
      _fromColorArray(
        position + 4,
        Array.append(
          acc,
          [|
            ofColor(
              colorArray[position + 0],
              colorArray[position + 1],
              colorArray[position + 2],
              colorArray[position + 3]
            )
          |]
        )
      );
    } else {
      acc;
    };
  _fromColorArray(0, [||]);
};

let getRange = pixelArray =>
  Array.fold_left(
    (ranges: option(colorRange), pixel) =>
      Some(reduceColorRange(pixel, ~ranges?, ())),
    None,
    pixelArray
  );

let sortPixelList = (pixelArray: array(pixel), colorRange) => {
  let deltaRed = colorRange.red.max -. colorRange.red.min;
  let deltaGreen = colorRange.green.max -. colorRange.green.min;
  let deltaBlue = colorRange.blue.max -. colorRange.blue.min;
  if (deltaRed > deltaGreen && deltaRed > deltaBlue) {
    let sortFn = (l: pixel, r: pixel) => int_of_float(l.red -. r.red);
    Array.sort(sortFn, pixelArray);
  } else if (deltaGreen > deltaBlue && deltaGreen > deltaRed) {
    let sortFn = (l: pixel, r: pixel) => int_of_float(l.green -. r.green);
    Array.sort(sortFn, pixelArray);
  } else {
    let sortFn = (l: pixel, r: pixel) => int_of_float(l.blue -. r.blue);
    Array.sort(sortFn, pixelArray);
  };
};

let colorAverage = pixelArray : pixel => {
  let squaredPixelArray =
    pixelArray
    |> Array.map((c: pixel) =>
         (
           {
             red: c.red *. c.red,
             green: c.green *. c.green,
             blue: c.blue *. c.blue
           }: pixel
         )
       );
  let squaredPixelsSum =
    Array.fold_left(
      (v: pixel, a: pixel) => {
        red: v.red +. a.red,
        green: v.green +. a.green,
        blue: v.blue +. a.blue
      },
      {red: 0., green: 0., blue: 0.},
      squaredPixelArray
    );
  {
    red: sqrt(squaredPixelsSum.red /. float_of_int(Array.length(pixelArray))),
    green:
      sqrt(squaredPixelsSum.green /. float_of_int(Array.length(pixelArray))),
    blue: sqrt(squaredPixelsSum.blue /. float_of_int(Array.length(pixelArray)))
  };
};

let clusterize = (pixelArray, square) => {
  let rec _clusterize = (clusters, square) =>
    if (square === 0) {
      clusters;
    } else {
      _clusterize(
        clusters
        |> Array.map(cluster => {
             let range = getRange(cluster);
             switch range {
             | None => [|cluster|]
             | Some(range) =>
               sortPixelList(cluster, range);
               [|
                 Array.sub(cluster, 0, Array.length(cluster) / 2),
                 Array.sub(
                   cluster,
                   Array.length(cluster) / 2,
                   Array.length(cluster) / 2
                 )
               |];
             };
           })
        |> Array.fold_left((acc, cluster) => Array.append(acc, cluster), [||]),
        square - 1
      );
    };
  _clusterize([|pixelArray|], square);
};

let paletteOfClusters = clusters => clusters |> Array.map(colorAverage);

let paletteOfPixelArray = (pixelArray, ~square=4, ()) =>
  paletteOfClusters(clusterize(pixelArray, square));

let ofImageData = (imageData, ~square=?, ()) =>
  paletteOfPixelArray(
    ofFloatArray(Webapi.ImageData.getData(imageData)),
    ~square?,
    ()
  );

[@gentype]
let ofUrl = (url, ~square=?, ()) =>
  Webapi.imageDataOfUrl(url)
  |> Js.Promise.then_(imageData =>
       Js.Promise.resolve(ofImageData(imageData, ~square?, ()))
     );
