defmodule UT2 do
    def randomStr(n, chars) do
        to_string(Enum.take_random(chars, n))
    end
    def randomStr2(n, chars) do
        to_string(for x <- 0..n-1, x < n, do: Enum.random(chars))
    end
end
defmodule JSON do
    def stringify(json) do
        case json do
            {:null} ->  "null"
            {:bool, x} when is_boolean(x) -> to_string(x)
            {:number, x} when is_number(x) -> to_string(x)
            {:string, x} when is_binary(x) -> inspect(x)
            {:array, x} when is_list(x) -> "[" <> Enum.join((for elem <- x, do: stringify(elem)), ",")  <> "]"
            {:object, x} -> "{" <> Enum.join((for {key, value} <- x, do:  key <>": " <> stringify(value)), ",") <> "}"
            _ -> "Error"
        end
    end
end
nums = {:array, [{:null}, {:bool, false}, {:number, 23}, {:string, "asdad"}]} 
#nums = Enum.map([1, 2, 3], &({:number, &1}))
IO.puts(JSON.stringify(nums)) # => "[1,2,3]"

fields = Enum.zip(["x", "y"], [bool: true, bool: false]) #Esta bien xd jajaaj si measuste
IO.puts(JSON.stringify({:object, fields})) 
#queres ver el mundo arder, jaja exacto
object = {:object, [
  {"x", {:number, 1}},
  {"y", {:array, []}},
  {"d", {:object, [
      {"a", {:string, "aber"}},
      {"null", {:null}}
  ]}}
]}
IO.puts(JSON.stringify(object))
#eso mismo, faltaba la key

"""
JSON.stringify({:null}) # => "null"
nums = Enum.map([1, 2, 3], &({:number, &1}))
JSON.stringify(nums) # => "[1,2,3]"
fields = Enum.zip(["x", "y"], [bool: true, bool: false])
JSON.stringify({:object, fields}) 

"{:null} # null
{:bool, true} # true
{:number, -12.34} # -12.34
{:string, \"This string.\"} # \"This string.\"
{:array, [{:null}, {:bool, false}]} # [null, false]
{:object, [ # {x: 1, y: []}
  {"x", {:number, 1}},
  {"y", {:array, []}} 
]}"

case 3 do
   1 -> IO.puts("Hi, I'm one")
   2 -> IO.puts("Hi, I'm two")
   3 -> IO.puts("Hi, I'm three")
   _ -> IO.puts("Oops, you dont match!")
end

Hi, I'm three
"""