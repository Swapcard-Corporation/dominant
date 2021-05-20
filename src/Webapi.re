module Image = {
  type t;
  [@bs.new] external create : unit => t = "window.Image";
  [@bs.set] external setSource : (t, string) => unit = "src";
  [@bs.set]
  external setOnload : (t, [@bs.this] (t => unit)) => unit = "onload";
  [@bs.get] external getWidth : t => float = "width";
  [@bs.get] external getNaturalWidth : t => float = "naturalWidth";
  [@bs.get] external getHeight : t => float = "height";
  [@bs.get] external getNaturalHeight : t => float = "naturalHeight";
};

module Element = {
  type t;
  [@bs.send.pipe : t] external setAttribute : (string, string) => unit = "setAttribute";
};

module Document = {
  type t;
  [@bs.send.pipe : t] external createElement : string => Element.t = "createElement";
};

module ImageData = {
  type t;
  [@bs.get] external getWidth : t => float = "width";
  [@bs.get] external getHeight : t => float = "height";
  [@bs.get] external getData : t => array(float) = "data";
};

[@bs.val] external document : Document.t = "document";

module CanvasContext = {
  type t;
  [@bs.send.pipe : t]
  external drawImage : (Image.t, float, float) => unit = "drawImage";
  [@bs.send.pipe : t]
  external getImageData : (float, float, float, float) => ImageData.t = "getImageData";
};

module Canvas = {
  type t;
  [@bs.send.pipe : Element.t]
  external getContext : string => CanvasContext.t = "getContext";
};

let onLoad = callback =>
  [@bs.this]
  (
    img => {
      let canvas = document |> Document.createElement("canvas");
      let context = canvas |> Canvas.getContext("2d");
      canvas
      |> Element.setAttribute("width", Js.Float.toString(Image.getWidth(img)));
      canvas
      |> Element.setAttribute("height", Js.Float.toString(Image.getHeight(img)));
      context |> CanvasContext.drawImage(img, 0.0, 0.0);
      let imageData =
        context |> CanvasContext.getImageData(0.0, 0.0, 0.0, 0.0);
      callback(imageData);
    }
  );

let imageDataOfUrl = url => {
  let img = Image.create();
  Js.Promise.make((~resolve, ~reject as _) => {
    Image.setOnload(img, onLoad(result => [@bs] resolve(result)));
    Image.setSource(img, url);
  });
};
