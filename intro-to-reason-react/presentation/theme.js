// example theme.js
import { future } from "mdx-deck/themes";
import okaidia from "react-syntax-highlighter/styles/prism/okaidia";
import prismReason from "react-syntax-highlighter/languages/prism/reason";

export default {
  ...future,
  prism: {
    // style: okaidia,
    languages: {
      reason: prismReason
    }
  },
  // css: {
  //   ...theme.css,
  //   textAlign: "left"
  // }
};

// import { future } from "mdx-deck/themes";
// import okaidia from "react-syntax-highlighter/styles/prism/okaidia";
// import prismReason from "react-syntax-highlighter/languages/prism/reason";

// export default {
//   ...future,

//   css: {
//     ...theme.css,
//     textAlign: "left"
//   },

//   prism: {
//     languages: {
//       reason: prismReason
//     }
//   }

// Customize your presentation theme here.
//
// Read the docs for more info:
// https://github.com/jxnblk/mdx-deck/blob/master/docs/theming.md
// https://github.com/jxnblk/mdx-deck/blob/master/docs/themes.md
// };
